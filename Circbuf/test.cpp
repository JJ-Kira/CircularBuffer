#include "gtest/gtest.h"
extern "C" {
  #include "circbuf.h"
}

TEST(CircularBuffer, Size)
{
  /* Create and initialize circular buffer */
  circbuf ring_buffer = circbuf_init(20);
  EXPECT_EQ(circbuf_size(ring_buffer), 20);
  EXPECT_EQ(circbuf_dataSize(ring_buffer), 0);

  circbuf_free(ring_buffer);
}

TEST(CircularBuffer, PopEmpty)
{
  char buf;
  
  circbuf ring_buffer = circbuf_init(20);

  EXPECT_EQ(circbuf_pop(ring_buffer, &buf, 1), 0);
  
  circbuf_free(ring_buffer);
}

TEST(CircularBuffer, PeekEmpty)
{
  char buf;
  
  circbuf ring_buffer = circbuf_init(20);

  EXPECT_EQ(circbuf_peek(ring_buffer, &buf, 1), 0);
  
  circbuf_free(ring_buffer);
}

TEST(CircularBuffer, PushPop)
{
  char buf_arr[50];
  
  circbuf ring_buffer = circbuf_init(20);
  
  circbuf_push(ring_buffer, "Hello, Circ Buffer!", 19);

  EXPECT_EQ(circbuf_dataSize(ring_buffer), 19);

  EXPECT_EQ(circbuf_pop(ring_buffer, buf_arr, 20), 19);
}

TEST(CircularBuffer, Overflow)
{
  char buf;
  char buf_arr[10];
  
  circbuf ring_buffer = circbuf_init(20);
  
  circbuf_push(ring_buffer, "Hello, Circ Buffer!", 19);
  circbuf_push(ring_buffer, "12345", 5);

  EXPECT_EQ(circbuf_pop(ring_buffer, buf_arr, 3), 3);
  EXPECT_EQ(circbuf_pop_single(ring_buffer, &buf), 1);
  EXPECT_EQ(circbuf_dataSize(ring_buffer), 16);
  EXPECT_EQ(buf, 'C');
}

TEST(CircularBuffer, SinglePushPop)
{
  char buf = 'A';
  
  circbuf ring_buffer = circbuf_init(20);
  
  circbuf_push_single(ring_buffer, &buf);
  circbuf_push_single(ring_buffer, &buf);
  circbuf_push_single(ring_buffer, &buf);
  circbuf_push_single(ring_buffer, &buf);
  circbuf_push_single(ring_buffer, &buf);

  EXPECT_EQ(circbuf_dataSize(ring_buffer), 5);

  circbuf_push(ring_buffer, "12345", 5);

  EXPECT_EQ(circbuf_dataSize(ring_buffer), 10);

  buf = 'a';
  circbuf_pop_single(ring_buffer, &buf);
  circbuf_pop_single(ring_buffer, &buf);
  circbuf_pop_single(ring_buffer, &buf);
  circbuf_pop_single(ring_buffer, &buf);
  circbuf_pop_single(ring_buffer, &buf);

  EXPECT_EQ(buf, 'A');
}