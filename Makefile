CC = g++
CFLAGS = -Wall -std=c++11

mock_terminal_client: mock_terminal_client.cpp
	$(CC) $(CFLAGS) -o mock_terminal_client mock_terminal_client.cpp

clean:
	rm -f mock_terminal_client
