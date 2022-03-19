#ifndef INFIXEXP_H
#define INFIXEXP_H


typedef struct ExpTreeNode *ExpTree;

typedef struct ExpTreeNode {
  TokenType tt;
  Token t;
  ExpTree left;
  ExpTree right;
} ExpTreeNode;

ExpTree newExpTreeNode(TokenType tt, Token t, ExpTree tL, ExpTree tR);
int valueIdentifier(List *lp, char **sp);
double valueExpTree(ExpTree tr);
int treePrefixExpression(List *lp, ExpTree *tp);
void printExpTreeInfix(ExpTree tr);
void prefExpTrees();
void freeExpTree(ExpTree tr);
int isOperator(char c);
int isNumerical(ExpTree tr);
int valueOperator(List *lp, char *cp);


int valueOperatorExp(List *lp, char *cp);
int valueOperatorTerm(List *lp, char *cp);
ExpTree treeInfixExpression(List *lp);
ExpTree treeInfixTerm(List *lp);
ExpTree treeInfixFactor(List *lp);
void infixExpTrees();

#endif
