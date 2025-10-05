#include "Polynomial.h"
#include <map>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

/* hidden global storage */
static int nextID = 0;
static std::map<int, std::map<int,int>> repo;
static std::map<const Polynomial*, int> registry;

// return id for object, create fresh storage entry if needed
static int getID_for(const Polynomial* p) {
    auto it = registry.find(p);
    if (it == registry.end()) {
        int id = ++nextID;
        registry[p] = id;
        repo[id] = std::map<int,int>();
        return id;
    }
    return it->second;
}

/* Implementations */

void Polynomial::insertTerm(int coefficient, int exponent) {
    if (coefficient == 0 || exponent < 0) return;
    int id = getID_for(this);
    auto &terms = repo[id];
    terms[exponent] += coefficient;
    if (terms[exponent] == 0) terms.erase(exponent);
}

std::string Polynomial::toString() const {
    int id = getID_for(this);
    auto it = repo.find(id);
    if (it == repo.end() || it->second.empty()) return "0";

    const auto &terms = it->second;
    std::ostringstream out;
    bool first = true;

    // iterate in descending exponent order
    std::vector<std::pair<int,int>> vec;
    for (const auto &kv : terms) vec.emplace_back(kv.first, kv.second);
    std::sort(vec.begin(), vec.end(), [](const auto &a, const auto &b){ return a.first > b.first; });

    for (const auto &p : vec) {
        int exp = p.first;
        int coeff = p.second;
        if (coeff == 0) continue;

        if (!first) {
            out << (coeff > 0 ? " + " : " - ");
        } else if (coeff < 0) {
            out << "-";
        }
        first = false;

        int absCoeff = std::abs(coeff);
        if (!(absCoeff == 1 && exp != 0)) out << absCoeff;

        if (exp > 0) {
            out << "x";
            if (exp > 1) out << "^" << exp;
        }
    }

    return out.str();
}

Polynomial Polynomial::add(const Polynomial& other) const {
    int id1 = getID_for(this);
    int id2 = getID_for(&other);

    std::map<int,int> temp = repo[id1];
    for (const auto &kv : repo[id2]) {
        temp[kv.first] += kv.second;
        if (temp[kv.first] == 0) temp.erase(kv.first);
    }

    Polynomial result;
    int rid = getID_for(&result);
    repo[rid] = std::move(temp);
    return result;
}

Polynomial Polynomial::multiply(const Polynomial& other) const {
    int id1 = getID_for(this);
    int id2 = getID_for(&other);

    std::map<int,int> temp;
    for (const auto &a : repo[id1]) {
        for (const auto &b : repo[id2]) {
            int e = a.first + b.first;
            int c = a.second * b.second;
            temp[e] += c;
            if (temp[e] == 0) temp.erase(e);
        }
    }

    Polynomial result;
    int rid = getID_for(&result);
    repo[rid] = std::move(temp);
    return result;
}

Polynomial Polynomial::derivative() const {
    int id = getID_for(this);
    std::map<int,int> temp;
    for (const auto &kv : repo[id]) {
        int exp = kv.first;
        int coeff = kv.second;
        if (exp > 0) temp[exp - 1] = coeff * exp;
    }

    Polynomial result;
    int rid = getID_for(&result);
    repo[rid] = std::move(temp);
    return result;
}
