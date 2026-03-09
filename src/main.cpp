#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
// Hàm test hệ thống phần cứng xe EIU MCR
void test() {
    // Đọc giá trị từ Dip Switch để chọn chế độ test
    unsigned char mode = get_dipsw(); 

    switch(mode) {
        // ---------------------------------------------------------
        // CASE 0: TEST MẠCH DÒ ĐƯỜNG (SENSOR)
        // ---------------------------------------------------------
        case 0: 
            // Ấn bất kỳ nút nhấn nào thì xe tự động cập nhật ADC của màu trắng
            if (get_key(KEY0) || get_key(KEY1) || get_key(KEY2) || get_key(KEY3)) {
                update_vcompare(); 
                // Có thể thêm hàm phát tiếng beep để báo hiệu đã cập nhật xong
            }
            
            // Đọc trạng thái 8 sensor và xuất ra 8 LED đơn để quan sát bằng mắt thường
            unsigned char sensor_status = sensor_inp(0xFF);
            led_put(sensor_status); 
            break;

        // ---------------------------------------------------------
        // CASE 1: TEST ĐỘNG CƠ BÁNH XE (MOTOR DC)
        // ---------------------------------------------------------
        case 1:
            // Test động cơ TRÁI
            if (get_key(KEY0)) {
                speed(100, 0);      // K0: Động cơ trái tiến
            } 
            else if (get_key(KEY1)) {
                speed(-100, 0);     // K1: Động cơ trái lùi
            }
            // Test động cơ PHẢI
            else if (get_key(KEY2)) {
                speed(0, 100);      // K2: Động cơ phải tiến
            } 
            else if (get_key(KEY3)) {
                speed(0, -100);     // K3: Động cơ phải lùi
            } 
            // Không nhấn gì thì dừng cả 2 động cơ
            else {
                speed(0, 0);
            }
            break;

        // ---------------------------------------------------------
        // CASE 2: TEST ĐỘNG CƠ ĐÁNH LÁI (RC SERVO)
        // ---------------------------------------------------------
        case 2:
            // Nhấn K0 hoặc K1 -> bẻ lái sang phải
            if (get_key(KEY0) || get_key(KEY1)) {
                handle(45); // Góc dương bẻ phải (có thể tùy chỉnh)
            }
            // Nhấn K2 hoặc K3 -> bẻ lái sang trái
            else if (get_key(KEY2) || get_key(KEY3)) {
                handle(-45); // Góc âm bẻ trái
            }
            // Không nhấn gì thì trả lái về thẳng tâm
            else {
                handle(0);
            }
            break;
    }
}