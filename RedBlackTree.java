
import java.util.Optional;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicReference;


public class RedBlackTree {

    public enum Color {
        RED,
        BLACK
    }

    public static class Node {
        int data;
        Color color;
        Node left;
        Node right;
        Node parent;
        boolean isNullLeaf;
    }

    private static Node createBlackNode(int data) {
        Node node = new Node();
        node.data = data;
        node.color = Color.BLACK;
        node.left = createNullLeafNode(node);
        node.right = createNullLeafNode(node);
        return node;
    }

    private static Node createNullLeafNode(Node parent) {
        Node leaf = new Node();
        leaf.color = Color.BLACK;
        leaf.isNullLeaf = true;
        leaf.parent = parent;
        return leaf;
    }

    private static Node createRedNode(Node parent, int data) {
        Node node = new Node();
        node.data = data;
        node.color = Color.RED;
        node.parent = parent;
        node.left = createNullLeafNode(node);
        node.right = createNullLeafNode(node);
        return node;
    }


    public Node insert(Node root, int data) {
        return insert(null, root, data);
    }


    public Node delete(Node root, int data) {
        AtomicReference<Node> rootReference = new AtomicReference<>();
        delete(root, data, rootReference);
        if(rootReference.get() == null) {
            return root;
        } else {
            return rootReference.get();
        }
    }

    public void printRedBlackTree(Node root) {
        printRedBlackTree(root, 0);
    }

    private void rightRotate(Node root, boolean changeColor) {
        Node parent = root.parent;
        root.parent = parent.parent;
        if(parent.parent != null) {
            if(parent.parent.right == parent) {
                parent.parent.right = root;
            } else {
                parent.parent.left = root;
            }
        }
        Node right = root.right;
        root.right = parent;
        parent.parent = root;
        parent.left = right;
        if(right != null) {
            right.parent = parent;
        }
        if(changeColor) {
            root.color = Color.BLACK;
            parent.color = Color.RED;
        }
    }

    private void leftRotate(Node root, boolean changeColor) {
        Node parent = root.parent;
        root.parent = parent.parent;
        if(parent.parent != null) {
            if(parent.parent.right == parent) {
                parent.parent.right = root;
            } else {
                parent.parent.left = root;
            }
        }
        Node left = root.left;
        root.left = parent;
        parent.parent = root;
        parent.right = left;
        if(left != null) {
            left.parent = parent;
        }
        if(changeColor) {
            root.color = Color.BLACK;
            parent.color = Color.RED;
        }
    }

    private Optional<Node> findSiblingNode(Node root) {
        Node parent = root.parent;
        if(isLeftChild(root)) {
            return Optional.ofNullable(parent.right.isNullLeaf ? null : parent.right);
        } else {
            return Optional.ofNullable(parent.left.isNullLeaf ? null : parent.left);
        }
    }

    private boolean isLeftChild(Node root) {
        Node parent = root.parent;
        if(parent.left == root) {
            return true;
        } else {
            return false;
        }
    }

    private Node insert(Node parent, Node root, int data) {
        if(root  == null || root.isNullLeaf) {
            if(parent != null) {
                return createRedNode(parent, data);
            } else {
                return createBlackNode(data);
            }
        }

        //duplicate insertion is not allowed for this tree.
        if(root.data == data) {
            throw new IllegalArgumentException("Duplicate date " + data);
        }

        boolean isLeft;
        if(root.data > data) {
            Node left = insert(root, root.left, data);

            if(left == root.parent) {
                return left;
            }

            root.left = left;

            isLeft = true;
        } else {
            Node right = insert(root, root.right, data);

            if(right == root.parent) {
                return right;
            }

            root.right = right;

            isLeft = false;
        }

        if(isLeft) {
            if(root.color == Color.RED && root.left.color == Color.RED) {

                Optional<Node> sibling = findSiblingNode(root);

                if(!sibling.isPresent() || sibling.get().color == Color.BLACK) {
                    if(isLeftChild(root)) {

                        rightRotate(root, true);
                    } else {

                        rightRotate(root.left, false);

                        root = root.parent;

                        leftRotate(root, true);
                    }

                } else {

                    root.color = Color.BLACK;
                    sibling.get().color = Color.BLACK;
                    if(root.parent.parent != null) {
                        root.parent.color = Color.RED;
                    }
                }
            }
        } else {

            if(root.color == Color.RED && root.right.color == Color.RED) {
                Optional<Node> sibling = findSiblingNode(root);
                if(!sibling.isPresent() || sibling.get().color == Color.BLACK) {
                    if(!isLeftChild(root)) {
                        leftRotate(root, true);
                    } else {
                        leftRotate(root.right, false);
                        root = root.parent;
                        rightRotate(root, true);
                    }
                } else {
                    root.color = Color.BLACK;
                    sibling.get().color = Color.BLACK;
                    if(root.parent.parent != null) {
                        root.parent.color = Color.RED;
                    }
                }
            }
        }
        return root;
    }


    private void delete(Node root, int data, AtomicReference<Node> rootReference) {
        if(root == null || root.isNullLeaf) {
            return;
        }
        if(root.data == data) {

            if(root.right.isNullLeaf || root.left.isNullLeaf) {
                deleteOneChild(root, rootReference);
            } else {

                Node inorderSuccessor = findSmallest(root.right);
                root.data = inorderSuccessor.data;
                delete(root.right, inorderSuccessor.data, rootReference);
            }
        }
        if(root.data < data) {
            delete(root.right, data, rootReference);
        } else {
            delete(root.left, data, rootReference);
        }
    }

    private Node findSmallest(Node root) {
        Node prev = null;
        while(root != null && !root.isNullLeaf) {
            prev = root;
            root = root.left;
        }
        return prev != null ? prev : root;
    }


    private void deleteOneChild(Node nodeToBeDelete, AtomicReference<Node> rootReference) {
        Node child = nodeToBeDelete.right.isNullLeaf ? nodeToBeDelete.left : nodeToBeDelete.right;
        replaceNode(nodeToBeDelete, child, rootReference);
        if(nodeToBeDelete.color == Color.BLACK) {

            if(child.color == Color.RED) {
                child.color = Color.BLACK;
            } else {

                deleteCase1(child, rootReference);
            }
        }
    }



    private void deleteCase1(Node doubleBlackNode, AtomicReference<Node> rootReference) {
        if(doubleBlackNode.parent == null) {
            rootReference.set(doubleBlackNode);
            return;
        }
        deleteCase2(doubleBlackNode, rootReference);
    }


    private void deleteCase2(Node doubleBlackNode, AtomicReference<Node> rootReference) {
        Node siblingNode = findSiblingNode(doubleBlackNode).get();
        if(siblingNode.color == Color.RED) {
            if(isLeftChild(siblingNode)) {
                rightRotate(siblingNode, true);
            } else {
                leftRotate(siblingNode, true);
            }
            if(siblingNode.parent == null) {
                rootReference.set(siblingNode);
            }
        }
        deleteCase3(doubleBlackNode, rootReference);
    }


    private void deleteCase3(Node doubleBlackNode, AtomicReference<Node> rootReference) {

        Node siblingNode = findSiblingNode(doubleBlackNode).get();

        if(doubleBlackNode.parent.color == Color.BLACK && siblingNode.color == Color.BLACK && siblingNode.left.color == Color.BLACK
                && siblingNode.right.color == Color.BLACK) {
            siblingNode.color = Color.RED;
            deleteCase1(doubleBlackNode.parent, rootReference);
        } else {
            deleteCase4(doubleBlackNode, rootReference);
        }
    }


    private void deleteCase4(Node doubleBlackNode, AtomicReference<Node> rootReference) {
        Node siblingNode = findSiblingNode(doubleBlackNode).get();
        if(doubleBlackNode.parent.color == Color.RED && siblingNode.color == Color.BLACK && siblingNode.left.color == Color.BLACK
                && siblingNode.right.color == Color.BLACK) {
            siblingNode.color = Color.RED;
            doubleBlackNode.parent.color = Color.BLACK;
            return;
        } else {
            deleteCase5(doubleBlackNode, rootReference);
        }
    }


    private void deleteCase5(Node doubleBlackNode, AtomicReference<Node> rootReference) {
        Node siblingNode = findSiblingNode(doubleBlackNode).get();
        if(siblingNode.color == Color.BLACK) {
            if (isLeftChild(doubleBlackNode) && siblingNode.right.color == Color.BLACK && siblingNode.left.color == Color.RED) {
                rightRotate(siblingNode.left, true);
            } else if (!isLeftChild(doubleBlackNode) && siblingNode.left.color == Color.BLACK && siblingNode.right.color == Color.RED) {
                leftRotate(siblingNode.right, true);
            }
        }
        deleteCase6(doubleBlackNode, rootReference);
    }


    private void deleteCase6(Node doubleBlackNode, AtomicReference<Node> rootReference) {
        Node siblingNode = findSiblingNode(doubleBlackNode).get();
        siblingNode.color = siblingNode.parent.color;
        siblingNode.parent.color = Color.BLACK;
        if(isLeftChild(doubleBlackNode)) {
            siblingNode.right.color = Color.BLACK;
            leftRotate(siblingNode, false);
        } else {
            siblingNode.left.color = Color.BLACK;
            rightRotate(siblingNode, false);
        }
        if(siblingNode.parent == null) {
            rootReference.set(siblingNode);
        }
    }

    private void replaceNode(Node root, Node child, AtomicReference<Node> rootReference) {
        child.parent = root.parent;
        if(root.parent == null) {
            rootReference.set(child);
        }
        else {
            if(isLeftChild(root)) {
                root.parent.left = child;
            } else {
                root.parent.right = child;
            }
        }
    }

    private void printRedBlackTree(Node root, int space) {
        if(root == null || root.isNullLeaf) {
            return;
        }
        printRedBlackTree(root.right, space + 5);
        for(int i=0; i < space; i++) {
            System.out.print(" ");
        }
        System.out.println(root.data + " " + (root.color == Color.BLACK ? "B" : "R"));
        printRedBlackTree(root.left, space + 5);
    }

    public static void main(String args[]) {

        Scanner scan = new Scanner(System.in);
        RedBlackTree redBlackTree = new RedBlackTree();
        Node root = null;
        char ch = '\n';
        Boolean getOut = true;

        do
        {
            System.out.println("\nRed Black Tree Operations\n");
            System.out.println("1. insert ");
            System.out.println("2. Delete");
            System.out.println("3. Exit");
            System.out.print("Enter your choice: ");

            int choice = scan.nextInt();
            switch (choice)
            {
                case 1 :
                    System.out.println("Enter integer element to insert");
                    root = redBlackTree.insert(root, scan.nextInt());

                    break;
                case 2 :
                    System.out.println("Enter integer element to delete");
                    root = redBlackTree.delete(root, scan.nextInt());
                    break;
                case 3 :
                    getOut =false;
                    break;
                default :
                    System.out.println("Wrong Entry \n ");
                    break;
            }

            redBlackTree.printRedBlackTree(root);
            if (getOut) {
                System.out.println("\nDo you want to continue (Type y or n) \n");
                ch = scan.next().charAt(0);
            }
        } while( (ch == 'Y'|| ch == 'y')&& getOut);

    }
}
