#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h>
#include "scanner.h"
#include "recognizeExp.h"
#include "evalExp.h"
#include "infixExp.h"


// checks for operators '+' and '-'
// changes pointers accordingly for TreeInfixExpression.
int valueOperatorExp(List *lp, char *cp) {

  if (*lp != NULL && (*lp)->tt == Symbol &&
      ((((*lp)->t).symbol == '+') || (((*lp)->t).symbol) == '-')) {
    *cp = ((*lp)->t).symbol;
    *lp = (*lp)->next;
    return 1;
  }

  return 0;
}

// checks for operators '*' and '/'
// changes pointers accordingly for TreeInfixTerm.
int valueOperatorTerm(List *lp, char *cp) {

  if (*lp != NULL && (*lp)->tt == Symbol &&
      ((((*lp)->t).symbol == '*') || (((*lp)->t).symbol) == '/')) {
    *cp = ((*lp)->t).symbol;
    *lp = (*lp)->next;
    return 1;
  }

  return 0;
}

// Main function that attempts to build a tree from a tokenlist.
ExpTree TreeInfixExpression(List *lp) {

  char c;
  Token t;
  ExpTree tr = NULL;

  // Base case, list is empty.
  if (*lp == NULL) {
    return NULL;
  }

  // Creates a tree from the left term of the expression.
  tr = treeInfixTerm(lp);

  //'+' or '-'
  while (valueOperatorExp(lp, &c)) {
    t.symbol = c;
    tr = newExpTreeNode(Symbol, t, tr, NULL);
    tr->right = treeInfixTerm(lp);
  }

  return tr;
}

ExpTree treeInfixTerm(List *lp) {

  char c;
  Token t;
  ExpTree tr = NULL;

  if (*lp == NULL) {
    return NULL;
  }

  tr = treeInfixFactor(lp);

  while (valueOperatorTerm(lp, &c)) {
    t.symbol = c;
    tr = newExpTreeNode(Symbol, t, tr, NULL);
    tr->right = treeInfixFactor(lp);
  }

  return tr;
}

ExpTree treeInfixFactor(List *lp) {

  double v;
  char *pc;
  Token t;
  ExpTree tr = NULL;

  if (*lp == NULL) {
    return NULL;
  }

  // if number
  if (valueNumber(lp, &v)) {
    t.number = (int)v;
    tr = newExpTreeNode(Number, t, NULL, NULL);
    return tr;
  }
  // if identifier
  else if (valueIdentifier(lp, &pc)) {
    t.identifier = pc;
    tr = newExpTreeNode(Identifier, t, NULL, NULL);
    return tr;
  }

  // if bracket
  else if (acceptCharacter(lp, '(')) {
    tr = TreeInfixExpression(lp);
    acceptCharacter(lp, ')');
  }
  return tr;
}

void infixExpTrees() {

  char *ar;
  List tl, tl2;
  ExpTree t = NULL;

  printf("give an expression: ");
  ar = readInput();

  while (ar[0] != '!') {

    tl = tokenList(ar);
    printList(tl);
    tl2 = tl;

    // Check if the expression is valid, if not skip the solver
    // and request a new expression.
    if (acceptExpression(&tl2) && tl2 == NULL) {
      t = TreeInfixExpression(&tl);
      printf("in infix notation: ");
      printExpTreeInfix(t);
      printf("\n");
      if (isNumerical(t)) {
        printf("the value is %g\n", valueExpTree(t));
      } else {
        printf("this is not a numerical expression\n");
      }
    } else {
      printf("this is not an expression\n");
    }

    freeExpTree(t);
    t = NULL;
    free(ar);
    freeTokenList(tl);
    freeTokenList(tl2);
    printf("\ngive an expression: ");
    ar = readInput();
  }
  free(ar);
  printf("good bye\n");
}
