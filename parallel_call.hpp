#ifndef PARALLEL_CALL_HPP
#define PARALLEL_CALL_HPP

#include <functional>
#include <iterator>
#include <shared_mutex>
#include <thread>
#include <vector>

/*
 * Accepts a range of callable objects [with operator()() implemented]. Launches
 * them all in different threads at the same time  (if enought cores are
 * available. Returns a vector with the results.
 */
template<class It>
auto parallel_call(It first, It last)
{
    using obj_t    = typename std::iterator_traits<It>::value_type;
    using diff_t   = typename std::iterator_traits<It>::difference_type;    
    using result_t = decltype(first->operator()());

    std::shared_mutex sm;
    const diff_t size = std::distance(first, last);
    std::vector<result_t> results(size);
    auto wait_then_call = [&sm](result_t& result, obj_t& f)
    {
	sm.lock_shared();
	result = f();
	sm.unlock_shared();
    };

    std::vector<std::thread> threads(size);
    sm.lock();
    for (diff_t i = 0; first != last; ++first, ++i)
	threads[i] = std::thread{wait_then_call,
				 std::ref(results[i]),
				 std::ref(*first)};
    sm.unlock();
    for (auto& t : threads)
	t.join();
    
    return results;
}

/*
 * Like parallel_call but for callable object which do not return anything.
 */
template<class It>
void parallel_call_void(It first, It last)
{
    using obj_t  = typename std::iterator_traits<It>::value_type;
    using diff_t = typename std::iterator_traits<It>::difference_type;
    
    std::shared_mutex sm;
    const diff_t size = std::distance(first, last);
    auto wait_then_call = [&sm](obj_t& f)
    {
	sm.lock_shared();
	f();
	sm.unlock_shared();
    };

    std::vector<std::thread> threads(size);
    sm.lock();
    for (diff_t i = 0; first != last; ++first, ++i)
	threads[i] = std::thread{wait_then_call, std::ref(*first)};
    sm.unlock();

    for (auto& t : threads)
	t.join();    
}

#endif // PARALLEL_CALL_HPP
