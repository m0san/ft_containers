//
// Created by moboustt on 19/8/2021.
//

#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <functional>
#include "../Utility/avltree.hpp"
#include "../Utility/reverse_iterator.hpp"
#include "../Utility/enable_if.hpp"
#include "../Utility/iterator_traits.hpp"
#include "../Utility/pair.hpp"

namespace ft
{

    template <class, class, class>
    class Node;

    template <
        typename Key,
        typename T,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {

    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_pointer;
        typedef typename avltree<value_type, Compare, Alloc>::Node Node;
        typedef avltree<value_type, Compare, Alloc> avltree;
        typedef Iterator<Node, value_type, Compare, Alloc, avltree> iterator;
        typedef Iterator<Node, const value_type, Compare, Alloc, avltree> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


        class value_compare
        {

        protected:
            explicit value_compare(Compare c) : comp(c) {}

            bool operator()(const value_type &lhs, const value_type &rhs) const
            {
                return comp(lhs.first, rhs.first);
            }

            Compare comp;
        };



        // Member functions ************************************************************************** //

        // Constructor, Destructor , copy assignment operator.
        map() : _tree(), _size(), _compare()
        {
            _tree.init(_compare, _alloc);
        }

        explicit map(const Compare &comp, const Alloc &alloc = Alloc())
            : _tree(), _alloc(alloc), _size(), _compare(comp) {
            _tree.init(_compare, _alloc);    
            }

        template <typename InputIt>
        map(InputIt first, InputIt last,const Compare &comp = Compare(),
            const Alloc &alloc = Alloc()) : _alloc(alloc), _compare(comp)
        {
            _tree.init(_compare, _alloc);
            for (; first != last; ++first)
                _tree.insert(*first);
            _size = _tree.size();
        }

        map(const map &other) {
            *this = other;
        }

        map &operator=(const map &other) {
            if (this != &other) {
                _tree = other._tree;
                _size = other._size;
           }
            return *this;
        }


        //  Iterators: ************************************************************************** //

        iterator begin() { return _tree.begin(); }

        iterator end() { return _tree.end(); }
        
        reverse_iterator rbegin() { return _tree.rbegin(); }

        reverse_iterator rend() { return _tree.rend(); }


        const_iterator begin() const { return _tree.begin(); }

        const_iterator end() const { return _tree.end(); }
        
        const_reverse_iterator rbegin() const { return _tree.rbegin(); }

        const_reverse_iterator rend() const { return _tree.rend(); }
 

        // Capacity: ************************************************************************** // 

        size_type size() const _NOEXCEPT { return _size; }

        bool empty() const _NOEXCEPT { return !_size; }

        size_type max_size() const _NOEXCEPT { return _alloc.max_size(); }


        // Element access: ************************************************************************** // 
        
        mapped_type &operator[](const Key &key)
        {
            return insert(ft::make_pair(key, mapped_type())).first->second;
        }

        ft::pair<iterator, bool> insert(const value_type &value)
        {
            ft::pair<iterator, bool> out = _tree.insert(value);
            if (out.second)
                _size++;
            return out;
        }

        iterator insert( iterator hint, const value_type& value ) {
            _tree.insert(hint, value);
        }
	
        template< class InputIt >
        void insert( InputIt first, InputIt last ) {
            for (; first != last; first++)
                insert(*first);
        }
        
        const avltree &getTree() const { return _tree; }

        /*
         * Rational Operators (==,!=,<,<=,>,>=,<=>)
         */

        friend bool operator==(const map &lhs, const map &rhs) { return (lhs.size() == rhs.size() && lhs._tree == rhs._tree); }

    private:
        avltree _tree;
        allocator_type _alloc;
        std::size_t _size;
        key_compare _compare;
    };

    //    template<class Key, class T, class Compare, class Alloc>
    //    bool operator==(const map<Key, T, Compare, Alloc> &lhs,
    //                    const map<Key, T, Compare, Alloc> &rhs) {
    //        return (lhs.size() == rhs.size() && lhs._tree == rhs._tree);
    //    }
}

#endif // __MAP_HPP__
