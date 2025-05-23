class Node:
     def __init__(self, value):
         self.value = value
         self.left = None
         self.right = None
def parse_tree(s):
     def parse_subtree(start):
         value = ''
         while start < len(s) and (s[start].isdigit() or s[start] == '-'):
             value += s[start]
             start += 1
         if not value:
             return None, start#
         node = Node(int(value))#
         if start < len(s) and s[start] == '(':
             start += 1
             node.left, start = parse_subtree(start)
             if start < len(s) and s[start] == ',':
                 start += 1
                 node.right, start = parse_subtree(start)
             if start < len(s) and s[start] == ')':
                 start += 1
#
         return node, start#
     tree, _ = parse_subtree(0)
     return tree

#Прямой обход: корень, левое поддерево, правое поддерево
def preorder_traversal(node):
    if node is None:
        return
    print(node.value, end=' ')
    preorder_traversal(node.left)
    preorder_traversal(node.right)#
 #Центральный обход: левое поддерево, корень, правое поддерево
def inorder_traversal(node):
    if node is None:
        return
    inorder_traversal(node.left)
    print(node.value, end=' ')
    inorder_traversal(node.right)

#Концевой обход: левое поддерево, правое поддерево, корень
def postorder_traversal(node):
    if node is None:
        return
    postorder_traversal(node.left)
    postorder_traversal(node.right)
    print(node.value, end=' ')#
def main():
    tree_string = '8(3(1,6(4,7)),10(,14(13,)))'
    root = parse_tree(tree_string)
    print("Прямой обход:")
    preorder_traversal(root)
    print()
    print("Центральный обход:")
    inorder_traversal(root)
    print()
    print("Концевой обход:")
    postorder_traversal(root)
    print()
if __name__ == '__main__':
     main()
