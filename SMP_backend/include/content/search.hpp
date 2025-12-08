#pragma once
#include <iostream>
#include <string>
#include "ADT/linked_list.hpp"
#include "core/user.hpp"
#include "content/post.hpp"
#include "interaction/message.hpp"

using namespace std;

class SearchEngine {
private:
    static const int ALPHABET_SIZE = 256;
    static const int RK_PRIME = 101;

    static void computeLPSArray(const string& pattern, int M, int* lps) {
        int len = 0;
        lps[0] = 0;
        int i = 1;
        while (i < M) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

    static bool KMPSearch(const string& text, const string& pattern) {
        int M = (int)pattern.length();
        int N = (int)text.length();
        if (M == 0) return false;
        if (M > N) return false;

        int* lps = new int[M];
        computeLPSArray(pattern, M, lps);

        int i = 0;
        int j = 0;
        bool found = false;

        while (i < N) {
            if (pattern[j] == text[i]) {
                j++;
                i++;
            }

            if (j == M) {
                found = true;
                break;
            } else if (i < N && pattern[j] != text[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }

        delete[] lps;
        return found;
    }

    static void badCharHeuristic(const string& str, int size, int badchar[ALPHABET_SIZE]) {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            badchar[i] = -1;

        for (int i = 0; i < size; i++)
            badchar[(int)str[i]] = i;
    }

    static bool BoyerMooreSearch(const string& text, const string& pattern) {
        int m = (int)pattern.size();
        int n = (int)text.size();
        if (m == 0) return false;
        if (m > n) return false;

        int badchar[ALPHABET_SIZE];
        badCharHeuristic(pattern, m, badchar);

        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && pattern[j] == text[s + j])
                j--;

            if (j < 0) {
                return true;
            } else {
                int shift = j - badchar[(int)text[s + j]];
                if (shift < 1) shift = 1; 
                s += shift;
            }
        }
        return false;
    }

    static bool RabinKarpSearch(const string& text, const string& pattern) {
        int M = (int)pattern.length();
        int N = (int)text.length();
        if (M == 0) return false;
        if (M > N) return false;

        int i, j;
        int p = 0;
        int t = 0;
        int h = 1;

        for (i = 0; i < M - 1; i++)
            h = (h * ALPHABET_SIZE) % RK_PRIME;

        for (i = 0; i < M; i++) {
            p = (ALPHABET_SIZE * p + pattern[i]) % RK_PRIME;
            t = (ALPHABET_SIZE * t + text[i]) % RK_PRIME;
        }

        for (i = 0; i <= N - M; i++) {
            if (p == t) {
                for (j = 0; j < M; j++) {
                    if (text[i + j] != pattern[j])
                        break;
                }
                if (j == M)
                    return true;
            }

            if (i < N - M) {
                t = (ALPHABET_SIZE * (t - text[i] * h) + text[i + M]) % RK_PRIME;
                if (t < 0)
                    t = (t + RK_PRIME);
            }
        }
        return false;
    }

public:
    static LinkedList<User*> searchUsers(const string& query, LinkedList<User*>& allUsers) {
        LinkedList<User*> results;
        if (query.empty()) return results;

        Node<User*>* curr = allUsers.getHead();
        while (curr) {
            if (KMPSearch(curr->data->getUsername(), query) || 
                KMPSearch(curr->data->getCity(), query)) {
                results.append(curr->data);
            }
            curr = curr->next;
        }
        return results;
    }

    static LinkedList<Post*> searchPosts(const string& query, LinkedList<Post*>& allPosts) {
        LinkedList<Post*> results;
        if (query.empty()) return results;

        Node<Post*>* curr = allPosts.getHead();
        while (curr) {
            if (BoyerMooreSearch(curr->data->content, query)) {
                results.append(curr->data);
            }
            curr = curr->next;
        }
        return results;
    }

    static LinkedList<Message> searchMessages(const string& query, LinkedList<Message>& chatHistory) {
        LinkedList<Message> results;
        if (query.empty()) return results;

        Node<Message>* curr = chatHistory.getHead();
        while (curr) {
            if (RabinKarpSearch(curr->data.getText(), query)) {
                results.append(curr->data);
            }
            curr = curr->next;
        }
        return results;
    }
};

