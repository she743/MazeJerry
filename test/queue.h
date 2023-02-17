namespace PQueue {
    struct Queue_Node {
        int loc;
        int parent;
        int ob;
        int g;
        int h;
        int f;
        struct Queue_Node* next;
    };

    class P_Queue {
        public:
            Queue_Node* qNode;
            P_Queue();
            bool is_empty(void);
            void enqueue(Queue_Node* node);
            bool find(int num);
            Queue_Node* dequeue(void);
            Queue_Node* findptr(int num);
            int find_parent(int num);
            Queue_Node* node_delete(int num);

        private:
            void apply(Queue_Node* input_node, Queue_Node* target_node);
    };
}