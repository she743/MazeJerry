namespace Sensing{
    struct SensorDataFrame {
        int l_data;
        int f_data;
        int r_data;
    };

    class Sensor{
        public:
            Sensor(int pin0, int pin1, int pin2);
            SensorDataFrame get();
            void cleanup();
        private:
            int left_pin;
            int forward_pin;
            int right_pin;

    };
}