/**
 * Stack.h - an adjustable fixed sized stack template
 *
 *  Example: to create a stack with max of 10 chars just do this:
 *  
 *  Stack<char, 10> myStack;
 *
 *  myStack.push('a');
 *  myStack.push('b');
 *  myStack.push('c');
 *  while(myStack.empty()) {
 *     char foo = myStack.pop();
 *  }
 *
 */

#ifndef _STACK_H_
#define _STACK_H_

/**
 * Fixed Size Stack Template
 */
template<typename T, int MAX_ITEMS>
class Stack {
private:
  T stackData[MAX_ITEMS]; // max number of items in this stack
  T* stackPtr;
  int top;
public:
  Stack();
  ~Stack() { }

  int empty() const { return top == -1; }
  int full() const { return top == MAX_ITEMS - 1; }
  T pop();
  void push(const T& item);
  int size() const { return top+1; }
};

/**
 * Fixed Size Stack Constructor
 */
template<typename T, int N>
Stack<T, N>::Stack():top(-1) {
  stackPtr = &stackData[0]; // initialize stackPt
}

/**
 * push a value on the stack
 */
template<typename T, int N>
void Stack<T, N>::push(const T& item) {
  if (!full()) {
	stackPtr[++top] = item;
  }
  // push unsuccessful
}

/**
 * pop a value off the stack
 */
template<typename T, int N>
T Stack<T, N>::pop() {
  if (!empty()) {
    return stackPtr[top--]; // pop successful
  }
  else {
    stackPtr[0]; // pop unsuccessful .. need to return something
  }
}
#endif 
