namespace MotorCTL{
    struct Instruct{
        int speed;
        bool dir;
    };

    class Motor{
        public:
            Motor(int r_fpin, int r_bpin, int l_fpin, int l_bpin );
            void move(Instruct instruction);
            void cleanup( void );
        private:
            int r_forward_pin;
            int r_backward_pin;
            int l_forward_pin;
            int l_backward_pin;

            void forward( int speed );
            void backward( void );
            void turn_right( void );
            void turn_left( void );
    };
}