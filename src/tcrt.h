namespace Tcrt{
    struct LineDataFrame {
        int left_d;
        int middle_d;
        int right_d;
    };

    class Line_Sensor{
        public:
            Line_Sensor(int pin0, int pin1, int pin2);
            LineDataFrame get();
            void cleanup();
        private:
            int l_pin;
            int m_pin;
            int r_pin;
    };    
}