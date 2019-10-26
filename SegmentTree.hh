#ifndef __SEGMENT_TREE__
#define __SEGMENT_TREE__

#include <vector>
#include <cmath>

// Op has to be an associative operation T x T -> T
// T has to implement a default constructor T() which is the identity for Op
template<class T, class Op>
class SegmentTree {
private:
    int sz;
    std::vector<T> tree;
    Op op;
    
    void build(const std::vector<T>& v, int curr, int left, int right) {
        if (left == right) tree[curr] = v[left];
        else {
            int mid = (left+right)/2;
            build(v, curr*2, left, mid);
            build(v, curr*2+1, mid+1, right);
            tree[curr] = op(tree[curr*2], tree[curr*2+1]);
        }
    }
    
    T aux_query(int curr, int curr_left, int curr_right, int left, int right) {
        if (curr_left > curr_right) return T();
        if (left > curr_right or right < curr_left) return T();
        //std::cout << curr << " " << curr_left << " " << curr_right << " " << left << " " << right << std::endl;
        if (left == curr_left and right == curr_right) return tree[curr];
        int curr_mid = (curr_left + curr_right)/2;
        return op(aux_query(curr*2, curr_left, curr_mid, left, std::min(right, curr_mid)),
                  aux_query(curr*2+1, curr_mid+1, curr_right, std::max(left, curr_mid+1), right));
    }
    
    void aux_update(int curr, int curr_left, int curr_right, int pos, const T& val) {
        if (curr_left == curr_right) tree[curr] = val;
        else {
            int curr_mid = (curr_left + curr_right)/2;
            if (pos <= curr_mid) {
                aux_update(curr*2, curr_left, curr_mid, pos, val);
            }
            else {
                aux_update(curr*2+1, curr_mid+1, curr_right, pos, val);
            }
            tree[curr] = op(tree[curr*2], tree[curr*2+1]);
        }    
    }
    
public:
    SegmentTree(int size) {
        sz = size;
        tree = std::vector<T>(4*sz, T());
        op = Op();
    }
    
    SegmentTree(const std::vector<T>& v) {
        sz = v.size();
        tree = std::vector<T>(4*sz, T());
        build(v, 1, 0, sz-1);
        op = Op();
    }

    // Returns the operation applied on the interval [left, right]
    T query(int left, int right) {
        if (left < 0 or left > right or right >= sz) return T();
        return aux_query(1, 0, sz-1, left, right); 
    }
    
    // Sets v[pos] = val
    bool update(int pos, const T& val) {
        if (pos < 0 or pos >= sz) return false;
        aux_update(1, 0, sz-1, pos, val);
        return true;
    }
};

#endif
