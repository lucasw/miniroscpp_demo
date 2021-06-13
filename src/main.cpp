/**
BSD 3-Clause License

Copyright (c) 2021, Lucas Walter
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <miniros/console.h>
#include <sensor_msgs/Image.hxx>

int main(int argc, char* argv[]) {
  ros::init(argc, argv, "miniroscpp_demo");

  ros::NodeHandle nh;

  ros::Publisher image_pub = nh.advertise<sensor_msgs::Image>("image", 10);

  ros::Rate loop_rate(3);

  const size_t width = 64;
  const size_t height = 48;

  sensor_msgs::Image msg;
  {
    msg.header.frame_id = "map";
    msg.encoding = "mono8";
    msg.is_bigendian = false;
    msg.step = width;
    msg.data.resize(width * height);
  }

  size_t count = 0;
  while (ros::ok()) {
    msg.header.seq = count;
    msg.header.stamp = ros::Time::now();

    for (size_t y = 0; y < height; ++y) {
      for (size_t x = 0; x < height; ++x) {
        const size_t ind = y * width + height;
        msg.data[ind] = (y + count) % 256;
      }
    }

    image_pub.publish(msg);

    count++;
  }

  return 0;
}
