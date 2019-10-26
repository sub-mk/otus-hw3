#ifndef OTUS_HW3_LIB_H
#define OTUS_HW3_LIB_H

#include <map>
#include <cassert>
#include <iostream>

namespace lib {

    using MapBasic = std::map<int, int>;

    template<class T>
    T create_map(int n) {
        assert(n >= 0);
        T fact_map;
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                fact_map[i] = 1;
            } else {
                fact_map[i] = fact_map[i-1] * i;
            }
        }
        return fact_map;
    }

    template<class T>
    void print_map(T fact_map, const std::string& map_name) {
        std::cout << "*** " << map_name << " ***" << std::endl;
        for (auto& element : fact_map) {
            std::cout << element.first << " " << element.second << std::endl;
        }
    }

    // custom allocator

    template <class T>
    class custom_allocator {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        custom_allocator() noexcept {}
        template <class U> custom_allocator (const custom_allocator<U>&) noexcept {}
        pointer allocate (std::size_t n) {
            return reinterpret_cast<T*>( ::operator new(n*sizeof(T)));

        }
        void deallocate (T* p, [[maybe_unused]] std::size_t n) {
            ::operator delete(p);
        }
        void construct(pointer p, const T& value) {
            new (p) T(value);
        }
        void destruct(pointer p) {
            p->~T();
        }
        pointer address(reference x) const {
            return const_cast<pointer>(address(const_cast<const_reference>(x)));
        }
        const_pointer address(const_reference x) const {
            return  std::allocator<T>().address(x);
        }
        size_type max_size() {
            return std::allocator<T>::max_size();
        }
    };
    template<typename T>
    bool operator == (const custom_allocator <T>&, const custom_allocator <T>&) {
        return true;
    }

    template<typename T>
    bool operator != (const custom_allocator <T>& lhs, const custom_allocator <T>& rhs) {
        return !(lhs == rhs);
    }
    using Common = std::common_type<int,int>::type;
    using MapWithAlloc = std::map<int,int,std::less<Common>,custom_allocator<std::pair<int,int>>>;


}

#endif //OTUS_HW3_LIB_H
