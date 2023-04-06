// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPrior(char op) {
  std::pair<char, int> prior1[6];
  switch (op) {
    case'(':
      prior1[0].first = '(';
      prior1[0].second = 0;
    case')':
      prior1[1].first = ')';
      prior1[1].second = 1;
    case'+':
      prior1[2].first = '+';
      prior1[2].second = 2;
    case'-':
      prior1[3].first = '-';
      prior1[3].second = 2;
    case'*':
      prior1[4].first = '*';
      prior1[4].second = 3;
    case'/':
      prior1[5].first = '/';
      prior1[5].second = 3;
  }
  int prior = -1;
  for (int j = 0; j < 6; ++j) {
    if (op == prior1[j].first) {
      prior = prior1[j].second;
      break;
    }
  }
  return prior;
}
std::string spc(const std::string& s) {
  if (s.length() <= 2) return s;
  int n = 2 - s.length() % 2;
  std::string r(s, 0, n);
  for (auto i = s.begin() + n; i != s.end();) {
    r += ' '; r += *i++;;
  }
  return r;
}
std::string infx2pstfx(std::string inf) {
  std::string work;
  TStack <char, 100> stack;
  for (auto& op : inf) {
    int prior = getPrior(op);
    if (prior == -1) {
      work += op;
    } else {
      if (stack.get() < prior || prior == 0 || stack.isEmpty()) {
        stack.push(op);
      } else if (op == ')') {
        char a = stack.get();
        while (getPrior(a) >= prior) {
          work += a;
          stack.pop();
          a = stack.get();
        }
        stack.pop();
      } else {
        char a = stack.get();
        while (getPrior(a) >= prior) {
          work += a;
          stack.pop();
          a = stack.get();
        }
        stack.push(op);
      }
    }
  }
  while (!stack.isEmpty()) {
    work += stack.get();
    stack.pop();
  }
  work = spc(work);
  return work;
}

int count(const int& n1, const int& n2, const int& oper) {
  switch (oper) {
    default:
      break;
    case'+': return n1 + n2;
    case'-': return n1 - n2;
    case'*': return n1 * n2;
    case'/': return n1 / n2;
  }
  return 0;
}
int eval(std::string pref) {
  TStack<int, 100> stack;
  std::string num = "";
  for (size_t i = 0; i < pref.size(); i++) {
    if (getPrior(pref[i]) == -1) {
      if (pref[i] == ' ') {
        continue;
      } else if (isdigit(pref[i+1])) {
        num += pref[i];
        continue;
      } else {
        num += pref[i];
        stack.push(atoi(num.c_str()));
        num = "";
      }
    } else {
      int n2 = stack.get();
      stack.pop();
      int n1 = stack.get();
      stack.pop();
      stack.push(count(n1, n2, pref[i]));
    }
  }
  return stack.get();
}
