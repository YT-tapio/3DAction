#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

namespace linq {

    template <typename T>
    class Enumerable {
    public:
        using value_type = T;

        Enumerable() = default;

        explicit Enumerable(std::vector<T> data) : data_(std::move(data)) {}

        template <typename Iter>
        Enumerable(Iter first, Iter last) : data_(first, last) {}

        // --- フィルタ・変換 ---

        template <typename Predicate>
        Enumerable<T> where(Predicate pred) const {
            std::vector<T> result;
            for (const auto& item : data_) {
                if (pred(item)) {
                    result.push_back(item);
                }
            }
            return Enumerable<T>(std::move(result));
        }

        template <typename Selector>
        auto select(Selector selector) const {
            using R = std::decay_t<std::invoke_result_t<Selector, const T&>>;
            std::vector<R> result;
            result.reserve(data_.size());
            for (const auto& item : data_) {
                result.push_back(selector(item));
            }
            return Enumerable<R>(std::move(result));
        }

        template <typename Selector>
        auto select_many(Selector selector) const {
            using SubContainer = std::decay_t<std::invoke_result_t<Selector, const T&>>;
            using R = std::decay_t<decltype(*std::begin(std::declval<SubContainer&>()))>;
            std::vector<R> result;
            for (const auto& item : data_) {
                auto sub = selector(item);
                for (auto&& elem : sub) {
                    result.push_back(std::forward<decltype(elem)>(elem));
                }
            }
            return Enumerable<R>(std::move(result));
        }

        Enumerable<T> distinct() const {
            std::vector<T> result;
            std::unordered_set<T> seen;
            for (const auto& item : data_) {
                if (seen.insert(item).second) {
                    result.push_back(item);
                }
            }
            return Enumerable<T>(std::move(result));
        }

        // take() の修正（括弧で囲むとマクロ展開を回避できる）
        Enumerable<T> take(std::size_t n) const {
            const std::size_t len = (std::min)(n, data_.size());
            return Enumerable<T>(data_.begin(), data_.begin() + static_cast<std::ptrdiff_t>(len));
        }

        Enumerable<T> skip(std::size_t n) const {
            if (n >= data_.size()) {
                return Enumerable<T>{};
            }
            return Enumerable<T>(data_.begin() + static_cast<std::ptrdiff_t>(n), data_.end());
        }

        Enumerable<T> reverse() const {
            std::vector<T> result(data_.rbegin(), data_.rend());
            return Enumerable<T>(std::move(result));
        }

        // --- ソート ---

        template <typename KeySelector>
        Enumerable<T> order_by(KeySelector selector) const {
            std::vector<T> result = data_;
            std::stable_sort(result.begin(), result.end(),
                [&](const T& a, const T& b) {
                    return selector(a) < selector(b);
                });
            return Enumerable<T>(std::move(result));
        }

        template <typename KeySelector>
        Enumerable<T> order_by_descending(KeySelector selector) const {
            std::vector<T> result = data_;
            std::stable_sort(result.begin(), result.end(),
                [&](const T& a, const T& b) {
                    return selector(b) < selector(a);
                });
            return Enumerable<T>(std::move(result));
        }

        // --- 判定・集計 ---

        bool any() const {
            return !data_.empty();
        }

        template <typename Predicate>
        bool any(Predicate pred) const {
            return std::any_of(data_.begin(), data_.end(), pred);
        }

        template <typename Predicate>
        bool all(Predicate pred) const {
            return std::all_of(data_.begin(), data_.end(), pred);
        }

        std::size_t count() const {
            return data_.size();
        }

        template <typename Predicate>
        std::size_t count(Predicate pred) const {
            return static_cast<std::size_t>(std::count_if(data_.begin(), data_.end(), pred));
        }

        T sum() const {
            return std::accumulate(data_.begin(), data_.end(), T{});
        }

        double average() const {
            if (data_.empty()) {
                throw std::out_of_range("Sequence contains no elements.");
            }
            return static_cast<double>(sum()) / static_cast<double>(data_.size());
        }

        // メンバ関数名の変更
        T min_value() const {
            if (data_.empty()) {
                throw std::out_of_range("Sequence contains no elements.");
            }
            return *std::min_element(data_.begin(), data_.end());
        }

        T max_value() const {
            if (data_.empty()) {
                throw std::out_of_range("Sequence contains no elements.");
            }
            return *std::max_element(data_.begin(), data_.end());
        }

        template <typename Acc, typename Func>
        Acc aggregate(Acc seed, Func func) const {
            return std::accumulate(data_.begin(), data_.end(), std::move(seed), func);
        }

        // --- 要素取得・終端操作 ---

        T first() const {
            if (data_.empty()) {
                throw std::out_of_range("Sequence contains no elements.");
            }
            return data_.front();
        }

        template <typename Predicate>
        T first(Predicate pred) const {
            auto it = std::find_if(data_.begin(), data_.end(), pred);
            if (it == data_.end()) {
                throw std::out_of_range("Sequence contains no matching element.");
            }
            return *it;
        }

        T first_or_default(T default_value = T{}) const {
            return data_.empty() ? std::move(default_value) : data_.front();
        }

        T last() const {
            if (data_.empty()) {
                throw std::out_of_range("Sequence contains no elements.");
            }
            return data_.back();
        }

        T last_or_default(T default_value = T{}) const {
            return data_.empty() ? std::move(default_value) : data_.back();
        }

        template <typename Action>
        void for_each(Action action) const {
            for (const auto& item : data_) {
                action(item);
            }
        }

        std::vector<T> to_vector() const {
            return data_;
        }

        // 範囲ベースforループ対応
        auto begin() const { return data_.begin(); }
        auto end() const { return data_.end(); }

    private:
        std::vector<T> data_;
    };

    // --- 生成ヘルパー ---

    template <typename Container>
    auto from(const Container& container) {
        using T = std::decay_t<decltype(*std::begin(container))>;
        return Enumerable<T>(std::begin(container), std::end(container));
    }

    template <typename T>
    Enumerable<T> from(std::initializer_list<T> list) {
        return Enumerable<T>(list.begin(), list.end());
    }

    inline Enumerable<int> range(int start, int count) {
        std::vector<int> result;
        if (count > 0) {
            result.reserve(static_cast<std::size_t>(count));
            for (int i = 0; i < count; ++i) {
                result.push_back(start + i);
            }
        }
        return Enumerable<int>(std::move(result));
    }

} // namespace linq