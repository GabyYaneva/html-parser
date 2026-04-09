Minimalist HTML Parser in C
A robust, low-level HTML Parser written in pure C. This project is designed to scan raw HTML strings, identify tags, extract attributes, and retrieve text content. It was developed to bridge the gap between raw web data (fetched via an HTTP client) and structured information.

🧩 Core Logic
The parser operates as a State Machine, scanning the input buffer character by character to distinguish between:

Tags: Identifying start tags (e.g., <div>) and end tags (</div>).

Attributes: Extracting key-value pairs like href="..." or src="...".

Content: Isolating the inner text between tags while ignoring metadata.

🛠️ Features
Lightweight & Fast: Minimal memory footprint, optimized for speed.

Tag Extraction: Specifically tuned to find links (<a>), images (<img>), and headers.

Self-Contained: No external dependencies like libxml2.

Buffer-Based: Designed to work directly with data received from network sockets.

parser main.c
Example
If you provide an HTML string to the parser:

C
char *html = "<html><body><a href='https://github.com'>Link</a></body></html>";
parse_html(html);
Output:

Plaintext
Found Tag: <html>
Found Tag: <body>
Found Link: https://github.com
Found Text: Link

🧠 Technical Challenges
State Management: Correctly handling nested tags and malformed HTML (which is common on the web).

Memory Safety: Managing string buffers and pointers without causing leaks or segmentation faults—a classic C challenge.

Character Encoding: Dealing with quotes, spaces, and special symbols within attributes.
