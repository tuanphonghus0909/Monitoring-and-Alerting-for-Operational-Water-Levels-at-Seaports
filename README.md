# Giám sát và Cảnh báo Mực Nước Khai Thác tại Cảng Biển
### Đặt bài toán
Trong bối cảnh toàn cầu hóa và sự phát triển không ngừng của ngành vận tải biển, bản thân là một người sinh ra và lớn lên tại Hải Phòng, tôi nhận thấy rằng các cảng biển ngày càng phải đối mặt với yêu cầu nâng cao năng lực tiếp nhận và vận hành các tàu có trọng tải lớn. Một trong những yếu tố then chốt ảnh hưởng trực tiếp đến sự an toàn và hiệu quả hoạt động của cảng là mực nước khai thác – độ sâu thực tế tại các khu vực tiếp nhận tàu thuyền.

Mực nước khai thác không chỉ đóng vai trò đảm bảo an toàn hàng hải, giúp các tàu thuyền tránh được nguy cơ mắc cạn, va chạm mà còn quyết định khả năng tiếp nhận tàu lớn và tối ưu hóa hiệu quả kinh tế của cảng. Đặc biệt, trong bối cảnh biến đổi khí hậu, mực nước tại cảng biển ngày càng có sự thay đổi thất thường do triều cường, dòng chảy và hiện tượng nước biển dâng. Việc giám sát mực nước liên tục và chính xác trở thành yêu cầu cấp thiết để đảm bảo vận hành ổn định của cảng biển, nâng cao năng lực cạnh tranh và tuân thủ các tiêu chuẩn quốc tế về an toàn hàng hải.

Tuy nhiên, việc đo lường và giám sát mực nước khai thác tại nhiều cảng biển hiện nay vẫn còn dựa vào các phương pháp thủ công hoặc thiết bị không đồng bộ, dẫn đến sai số cao và khả năng phản ứng chậm trước các tình huống khẩn cấp. Điều này không chỉ ảnh hưởng đến hiệu quả khai thác cảng mà còn làm gia tăng nguy cơ xảy ra các sự cố hàng hải, gây thiệt hại lớn về kinh tế và môi trường.

### Nội dung chính
Từ vấn đề trên, thiết kế một hệ thống IOT giám sát mực nước khai thác tại cảng biển và cung cấp cảnh báo trực quan cũng như điều khiển ra hiệu cho tàu, hệ thống được thiết kế như sau:

***Cảm biến đo mực nước (Water Sensor):***
  Sử dụng cảm biến đo mực nước để thu thập dữ liệu mực nước theo thời gian thực.
  Kết nối cảm biến với ESP32, dữ liệu từ cảm biến sẽ được đọc và xử lý liên tục.
  
***ESP32 làm bộ điều khiển trung tâm:***
  - Cảnh báo tại chỗ: Dựa trên dữ liệu từ cảm biến, ESP32 điều khiển LED RGB để đưa ra cảnh báo trực quan:
  
    + Màu xanh lá: Mực nước an toàn.
    + Màu vàng: Mực nước gần mức nguy hiểm.
    + Màu đỏ: Mực nước dưới ngưỡng an toàn.
    
  - Truyền dữ liệu: ESP32 đẩy dữ liệu mực nước qua giao thức MQTT lên máy chủ (cloud hoặc cục bộ).
  
***Hệ thống MQTT:***

  - ESP32 (Publisher): Gửi thông tin mực nước đến broker MQTT.
  - Người giám sát (Subscriber): Nhận dữ liệu mực nước qua ứng dụng MQTT (ví dụ: smartphone, máy tính).
  - Gửi lệnh điều khiển: Người giám sát có thể gửi lệnh từ ứng dụng MQTT để điều khiển servo trên ESP32.
  
***Điều khiển cờ báo hiệu:***
  - ESP32 nhận lệnh từ MQTT để điều khiển servo quay cờ:
    + Cờ xanh: Tín hiệu cho phép tàu qua.
    + Cờ đỏ: Tín hiệu cấm tàu qua do mực nước không an toàn. 
### Sơ đồ khối dự kiến
![Hình 1](https://github.com/user-attachments/assets/b8ee558f-c87c-40b4-842d-002a7d4b914a)
*Hình 1*
### Mục tiêu đề tài
Đề tài này xây dựng hệ thống giám sát và cảnh báo mực nước tại cảng biển sử dụng IoT. Mục tiêu chính là đo mực nước bằng cảm biến và vi điều khiển ESP32, cảnh báo qua LED RGB (xanh, vàng, đỏ) tùy vào mức độ an toàn của mực nước. Dữ liệu sẽ được đẩy lên MQTT để giám sát từ xa và có thể điều khiển cờ xanh/đỏ qua servo, giúp tàu thuyền nhận thông báo để ra vào cảng an toàn. Hệ thống này giúp cải thiện hiệu quả vận hành và giảm thiểu rủi ro tại cảng.
