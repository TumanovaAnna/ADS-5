// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int priority(char x) {
  switch (x) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
      return 2;
    case '-':
      return 2;
    case '*':
      return 3;
    case '/':
      return 3;
    default:
      return -1;
    }
}
std::string infx2pstfx(std::string inf) {
    std::string post;
    int i = 0;
    char x = inf[i];
    char tmp = 0;
    TStack <char, 100> stackChar;
    while (x) {
    int pr1;
    pr1 = priority(x);
    if (pr1 > -1) {
      if ((pr1 == 0 || pr1 > priority(tmp) || stackChar.isEmpty()) && x != ')') {
          if (stackChar.isEmpty())
            tmp = x;
            stackChar.push(x);
    } else if (x == ')') {
        while (stackChar.get() != '(') {
          post.push_back(stackChar.get());
          post.push_back(' ');
          stackChar.pop();
    }
      stackChar.pop();
      if (stackChar.isEmpty())
        tmp = 0;
    } else {
        while (!stackChar.isEmpty() && priority(stackChar.get()) >= pr1) {
          post.push_back(stackChar.get());
          post.push_back(' ');
          stackChar.pop();
    }
    if (stackChar.isEmpty())
      tmp = x;
      stackChar.push(x);
        }
    } else {
        post.push_back(x);
        post.push_back(' ');
    }
    x = inf[++i];
    }
    while (!stackChar.isEmpty()) {
        post.push_back(stackChar.get());
        post.push_back(' ');
        stackChar.pop();
        }
    post.erase(post.end() - 1, post.end());
    return post;
}
int calculating(char oper, int n1, int n2) {
    switch (oper) {
      case '+':
        return n1 + n2;
        break;
      case '-':
        return n1 - n2;
        break;
      case '*':
        return n1 * n2;
        break;
      case '/':
        return n1 / n2;
        break;
    }
    return 0;
}
int eval(std::string post) {
    TStack <int, 100> stackInt;
    int i = 0, rsl = 0;
    char x = post[i];
    while (x) {
      if (x >= '0' && x <= '9') {
      int insertInt = 0;
      int y = 1;
    while (x != ' ') {
      inInt += (x - 48) * y;
      y *= 10;
      x = post[++i];
    }
    stackInt.push(inInt);
    } else {
      char oper = x;
        i++;
        int n2 = stackInt.get();
        stackInt.pop();
        int n1 = stackInt.get();
        stackInt.pop();
        int rsl = calculating(oper, n1, n2);
        stackInt.push(rsl);
    }
    if (i < post.size())
    x = post[++i];
    else
        x = 0;
    }
    rsl = stackInt.get();
    stackInt.pop();
    return rsl;
}
