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
            void enqueue(Queue_Node* node);
            bool find(int num);
            Queue_Node* dequeue(void);
            Queue_Node* findptr(int num);

        private:
            void apply(Queue_Node* input_node, Queue_Node* target_node);
    };
}