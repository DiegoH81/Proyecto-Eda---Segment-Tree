#include "node.h"

// Constructores
node::node() :
    start(-1), end(-1), left(nullptr), right(nullptr), top_topics(), height(-1), k_topics(-1) {}

node::node(int in_start, int in_end, topic_vector in_t_topics, size_t in_height, size_t in_k_topics, node* in_left, node* in_right)
    :start(in_start), end(in_end), top_topics (in_t_topics), height(in_height), k_topics(in_k_topics), left(in_left), right(in_right) {}

// Funciones
bool node::isLeaf() { return !left && !right; }

void node::update_height()
{
    size_t l_height = (left? left->height : 0 );
    size_t r_height = (right ? right->height : 0);

    height = std::max(l_height, r_height) + 1;
}

void node::merge()
{
    std::unordered_map <size_t, size_t> helper;


    if (left)
    {
        for (auto& data : left->top_topics)
            helper[data.first] += data.second;
    }

    if (right)
    {
        for (auto& data : right->top_topics)
            helper[data.first] += data.second;
    }

    std::vector<std::pair<size_t, size_t>> new_order;
    new_order.reserve(helper.size());

    for (auto& item : helper)
        new_order.push_back({ item.first, item.second });

    std::sort(new_order.begin(), new_order.end(), topic_cmp);
    if (new_order.size() > k_topics)
        new_order.resize(k_topics);

    top_topics = new_order;
}


bool topic_cmp(std::pair<size_t, size_t>& a, std::pair<size_t, size_t>& b)
{
    return a.second > b.second;
}