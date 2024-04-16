# Simple HTTP Server in C with Winsock

This project is a simple HTTP server implemented in C using the Winsock API. It can serve static HTML files to web clients over HTTP.

The project is inspired by Computerphile's Rust 25-line web server created in https://www.youtube.com/watch?v=7GBlCinu9yg.

- **`include/`**: Contains header files (`*.h`) for the project.
- **`src/`**: Contains source files (`*.c`) for the project.
- **`index.html`**: Sample HTML file served by the server.

## How to Build and Run

To build the project, compile all source files together with the `gcc` compiler:
```bash
gcc -o server src/server.c src/socket.c src/connection.c -lws2_32
```

To run the server, execute the generated `server` executable:
```bash
./server
```

The server will listen for incoming connections on port 9999 by default.

## Usage

Once the server is running, you can access the served content by opening a web browser and navigating to `http://127.0.0.1:9999/`.