# TCP Subnet Scanner

A lightweight, multi-host network scanner written in C. 
This tool iterates through a local subnet range (e.g., `192.168.1.x`) and attempts to establish TCP connections to a specific target port to identify active hosts or services.

> **Note:** This tool currently defaults to scanning **Port 53 (DNS)** on the `192.168.1.0/24` subnet.

## 🚀 Features
- **Subnet Sweeping:** Automatically generates and checks IP addresses from `192.168.1.1` to `192.168.1.254`.
- **Fast Scanning:** Implements socket timeouts (`SO_SNDTIMEO` / `SO_RCVTIMEO`) to prevent hanging on unresponsive hosts.
- **Connection Validation:** Uses the standard TCP 3-way handshake mechanism via the `connect()` system call to verify open ports.
- **Minimalist:** Built with standard POSIX libraries, requiring no external dependencies.

## 🛠️ Tech Stack
- **Language:** C
- **Libraries:** `<sys/socket.h>`, `<arpa/inet.h>`, `<unistd.h>`
- **Core Concepts:** Socket Programming, TCP/IP, Timeout Management.

## 📦 Installation & Usage

### 1. Compile the Code
Use GCC to build the scanner.
```
gcc tcp.c -o scanner
./scanner
```

## ⚙️ How It Works: The Logic

The program follows a simple linear scanning algorithm:

1.  **Looping:** A `for` loop iterates from 1 to 254.
2.  **String Formatting:** It constructs the target IP string dynamically (e.g., `"192.168.1.55"`) using `sprintf`.
3.  **Socket Creation:** A standard TCP stream socket is created for each iteration.
4.  **Timeout Configuration:**
    * To ensure speed, `setsockopt` is used to define a **0.1 second** (100,000 microsecond) timeout.
    * If a host doesn't answer instantly, the scanner moves on.
5.  **Connection Attempt:** It calls `connect()`.
    * **Returns 0:** Success (Port is Open).
    * **Returns -1:** Fail (Host down or Port Closed).

## 🤝 Contribution
Contributions are welcome! If you want to improve this tool, here are some great features to work on:

- [ ] **Full Port Scan Mode:** Add functionality to scan *some* common ports on a single specific IP address (to see everything running on one machine).
- [ ] **Command Line Arguments:** Update `main()` to accept the Subnet and Port via command line flags (e.g., `./scanner -p 80 -r 192.168.1.x`) instead of hardcoding them.
- [ ] **Multi-threading:** Implement threads to scan multiple IPs simultaneously for faster performance.

### How to Contribute
1.  Fork the repository.
2.  Create a new branch (`git checkout -b feature-new-scan-mode`).
3.  Commit your changes.
4.  Push to the branch and open a **Pull Request**.