namespace PStack{
    struct Stack_Node {
        int loc;
        int parent;
        struct Stack_Node* next;
    };

    class P_Stack {
        public:
            Stack_Node* top;
            P_Stack();
            void push(Stack_Node* s_node);
            Stack_Node* pop() ;

        private:
            void apply(Stack_Node* input_node, Stack_Node* target_node);
    };
}
