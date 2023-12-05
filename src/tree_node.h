#pragma once

#include <utility>
#include <list>
#include <functional>
#include <iostream>
#include <iomanip>

namespace ka
{
    template <typename T>
    class tree_node
    {
    public:
        template <typename... Args>
        tree_node(tree_node *parent, Args &&...args) : m_parent(parent),
                                                       m_data(std::forward<Args>(args)...)
        {
        }

        const T &data() const
        {
            return m_data;
        }

        T &data()
        {
            return m_data;
        }

        template <typename... Args>
        tree_node<T> &add_node(Args &&...args)
        {
            return m_children.emplace_back(this, std::forward<Args>(args)...);
        }

        void erase()
        {
            if (m_parent)
            {
                auto this_iter = std::find_if(m_parent->m_children.begin(),
                                              m_parent->m_children.end(),
                                              [this](const tree_node &node)
                                              { return &node == this; });

                m_parent->m_children.erase(this_iter);
            }
            else
            {
                m_children.clear();
                m_data = std::move(T());
            }
        }

        void dump(const size_t &indentation = 0, std::ostream &stream = std::cout) const
        {
            std::function<void(const tree_node &, size_t)> dump_recursive = [&](const tree_node &node, const size_t &indentation)
            {
                stream << std::setw(static_cast<int>(indentation) + 1) << node.m_data << '\n';

                for (const auto &child : node.m_children)
                    dump_recursive(child, indentation + 2);
            };

            dump_recursive(*this, indentation);
        }

    private:
        tree_node *m_parent;
        T m_data;
        std::list<tree_node> m_children;
    };
}