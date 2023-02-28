namespace MotorCTL{

    class Motor{
        public:
            Motor(int r_fpin, int r_bpin, int l_fpin, int l_bpin );
            void cleanup( void );
            void forward( void );
            void stop( void );
            void turn_right( void );
            void turn_left( void );
            void calibL( void );
            void calibR( void );
            void calibLL( void );
            void calibRR( void );
        private:
            int r_forward_pin;
            int r_backward_pin;
            int l_forward_pin;
            int l_backward_pin;
    };
}