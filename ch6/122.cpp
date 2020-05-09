// UVa122 Trees on the Level
// wangqc

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 300;
bool error;

struct Node
{
    bool used;
    int v;
    Node *left, *right;
    Node(): used(false), left(NULL), right(NULL) {}
};

Node *root;
char s[maxn];

void cleanup(Node* node) 
{
  if(node == NULL) return;
  cleanup(node->left);
  cleanup(node->right);
  delete node;
}

void addnode(int v, char* s)
{
    int n = strlen(s);
    Node *node = root;
    for (int i = 0; i < n; i ++)
    {
        if (s[i] == 'L')
        {
            if (node->left == NULL) node->left = new Node();
            node = node->left;
        }
        else if (s[i] == 'R')
        {
            if (node->right == NULL) node->right = new Node();
            node = node->right;
        }
    }
    if (node->used) error = true;
    node->v = v, node->used = true;
}

bool read_input()
{
    error = false;
    cleanup(root);
    root = new Node();
    for(;;)
    {
        if (scanf("%s", s) != 1) return false;
        if (!strcmp(s, "()")) break;
        int v;
        sscanf(&s[1], "%d", &v);
        addnode(v, strchr(s, ',')+1);
    }
    return true;
}

bool bfs(vector<int> &nodes)
{
    queue<Node*> q;
    nodes.clear();
    q.push(root);
    while (!q.empty())
    {
        Node *node = q.front(); q.pop();
        if (!node->used) return false;
        nodes.push_back(node->v);
        if (node->left != NULL) q.push(node->left);
        if (node->right != NULL) q.push(node->right);
    }
    return true;
}

int main()
{
    vector<int> nodes;
    while (read_input())
    {
        if (!bfs(nodes)) error = true;
        if (error) printf("not complete\n");
        else
        {
            for (int i = 0; i < nodes.size(); i++)
            {
                if (i) printf(" ");
                printf("%d", nodes[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
