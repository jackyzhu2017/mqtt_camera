# mqtt_camera
This project will implement real-time camera video transfer from edge to cloud using mqtt service.

Some notes:
1. QT need use mqtt client lib:
mqtt lib: git clone git://code.qt.io/qt/qtmqtt.git -b 6.7.3

2. Install mqtt server in ubuntu:
![image](https://github.com/user-attachments/assets/49c11a64-3f78-4100-be23-8291549a7a81)

3. Check emqx running status:
![image](https://github.com/user-attachments/assets/e3bd3faa-bce4-4cff-bd31-e59cce8fce35)

4. How to access the dashboard deployed in the Aliyun cloud:
   ssh -L 18083:127.0.0.1:18083 username@xx.xx.xx.xx (public cloud IP)

5. Check ports for emqx opened in Aliyun cloud management board:
![image](https://github.com/user-attachments/assets/bf7b1c08-1b2b-4248-8809-49fd57ef1fcb)

