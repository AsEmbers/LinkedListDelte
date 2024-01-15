#include <stdio.h>
#include <stdlib.h>

/**
 * 链表删除：
 *   1.定义链表结构类型
 *   2.声明链表结构类型指针变量
 *   3.声明删除函数，确定形参及返回值
 *   4.实现算法步骤：
 *     （1）找到需要删除节点的前驱节点，并判断其是否存在
 *     （2）定义临时节点指针变量，用来存放需删除节点的地址
 *     （3）将需被删除节点的后继节点的地址值赋给（1）中前驱节点的next指针变量
 *     （4）释放临时节点指针变量所指向的空间，即被删除节点
 */
typedef int ElemType;
typedef struct Node{
    ElemType data;
    struct Node *next;
}Node,*LinkedList;

//初始化链表，建立头节点
void init_linked_list(LinkedList &list){
    list=(Node*)malloc(sizeof(Node));
    list->data=NULL;
    list->next=NULL;
}
/**
 * 尾插法新增结点
 * @param list
 */
void insert_node_from_tail(LinkedList list){
    //声明新节点，临时尾节点（用来存放每次新增节点后链表的尾节点的地址，便于指向下一次的新增节点）
    Node *new_node,*temp_tail_node;
    //读取第一个元素
    ElemType elem;
    //读取第一个元素时，头节点即是尾节点
    temp_tail_node=list;
    scanf("%d",&elem);
    while (9999!=elem){
        new_node=(Node*)malloc(sizeof(Node));
        new_node->data=elem;
        temp_tail_node->next=new_node;
        //每次新增节点后，链表的尾节点都是最新插入的节点
        temp_tail_node=new_node;
        //循环读取新输入的元素
        scanf("%d",&elem);
    }
    temp_tail_node->next=NULL;
}

void print_list(LinkedList list){
    //取第一个节点
    Node *node=list->next;
    while (NULL!=node){
        printf("%3d",node->data);
        node=node->next;
    }
    printf("\n");
}
/**
 * 查找元素
 * @param list 链表指针变量
 * @param position 查找位置
 * @return
 */
Node* locate_element(LinkedList list,int position){
    if (position<0){
        return NULL;
    }
    Node *node=list->next;
    for (int i = 1; i < position && NULL!=node; i++) {
        node=node->next;
    }
    return node;
}
/**
 * 插入结点
 * @param list 链表指针变量
 * @param position 需要插入的位置
 * @param element 需要插入的元素
 * @return
 */
bool insert_node_from_position(LinkedList list,int position,ElemType element){
    if (position<1){
        return false;
    }
    Node *previous_node,*new_node;
    previous_node=locate_element(list,position-1);
    if (NULL==previous_node){
        return false;
    }
    new_node=(Node*)malloc(sizeof(Node));
    new_node->data=element;
    //令原链表前驱节点的后继节点成为新节点的后驱节点
    new_node->next=previous_node->next;
    //令原链表前驱节点的后继节点成为新节点
    previous_node->next=new_node;
    return true;
}
/**
 * 删除结点
 * @param list 链表指针变量
 * @param position 需要删除的位置
 * @return
 */
bool delete_node_by_position(LinkedList list,int position){
    if (position<1){
        return false;
    }
    Node *previous_node,*delete_node;
    previous_node=locate_element(list,position-1);
    if (NULL==previous_node){
        return false;
    }
    //获取需要删除的节点地址，并存储
    delete_node=previous_node->next;
    if (NULL==delete_node){
        return false;
    }
    //令原链表需要删除节点的后继节点成为其前驱节点的新后继节点，断链
    previous_node->next=delete_node->next;
    free(delete_node);
    delete_node=NULL;//为了避免野指针
    return true;
}

int main() {
    LinkedList list;
    init_linked_list(list);
    insert_node_from_tail(list);
    print_list(list);
    Node *node;
    node=locate_element(list,2);
    if (NULL!=node){
        printf("%d\n",node->data);
    }
    bool ret;
    ret=insert_node_from_position(list,2,99);
    if (ret) print_list(list);
    ret=delete_node_by_position(list,4);
    if (ret) print_list(list);
    return 0;
}
