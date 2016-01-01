# photon-web-display
Spark Photon web interface for displaying messages using publish/subscribe

Usage

1. Setup your Photon
2. Upload this firmware with Adafruit_SSD1306 library included to your Photon using build.particle.io or any other method
3. Publish messages to the "general-information" queue, marking them as private and replacing ```<YOUR_ACCESS_TOKEN>``` with proper value for your device:
  ```
  curl https://api.particle.io/v1/devices/events -d "name=general-information" -d "data=Help me, Obi Wan, you're my only hope!" -d "private=true" -d "ttl=60" -d access_token=<YOUR_ACCESS_TOKEN>
  ```
4. There is a special command to clear the whole display: ```%RESET_DISPLAY%```. Send it as a normal message to the same queue.
