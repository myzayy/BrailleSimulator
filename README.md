# BrailleSimulator (Braille Printer)

A high-performance C-based application designed to translate English text into Braille binary format and visualize it as an ASCII grid. The program is optimized for low memory footprint and ensures data integrity through custom headers and checksums.

## Data Storage Architecture

### Binary File Format
Data is stored in a custom binary format consisting of two main segments:

1.  **Header (`BrailleHeader`):** A fixed-size structure (32 bytes) containing metadata:
    * **Signature:** "BRL1" identifier.
    * **Version & Mode:** Metadata for compatibility checks.
    * **Character Count:** Total number of translated symbols.
    * **Checksum:** Integrity value to prevent data corruption.
2.  **Payload:** A sequence of bytes (`uint8_t`) where each byte represents one Braille character. 
    * **Encoding:** Based on a bitmask where Bit 0 corresponds to Dot 1, Bit 1 to Dot 2, and so on.

### Memory Profile (RAM Usage)
The application is designed using **stream processing**, ensuring a very small and constant memory footprint.
* **Memory Type:** Primarily stack memory (a few kilobytes).
* **Justification:** * The program does not load the entire file into RAM.
    * It utilizes a fixed-size `uint8_t buffer[20]` for line-by-line processing.
    * Memory consumption is $O(1)$—it remains constant regardless of whether the input file is 1 KB or 1 GB.

---

## Core Functions

| Function Header | Description |
|:--- |:--- |
| `int process_file(...)` | The main engine for **Translation Mode (-t)**. Reads text char-by-char, converts to Braille, and writes the binary file with a header. |
| `int print_to_braille_file(...)` | The core of **Printer Mode (-p)**. Validates the header/checksum and visualizes Braille codes as an ASCII grid. |
| `int char_to_braille(...)` | The "brain" of the translator. Maps ASCII symbols to Braille bitmasks (handles digits and uppercase prefixes). |
| `int count_dots_in_byte(...)` | Utility function for statistics. Calculates the number of active dots in a Braille character. |
| `void print_usage(...)` | Displays CLI instructions in case of invalid arguments. |

---

## Features, Limitations & Roadmap

### Key Features
* **Integrity Protection:** Implemented **Checksum** verification. The program detects if a single byte has been corrupted or altered.
* **Horizontal Visualization:** Unlike simple vertical output, it uses a 20-character buffer to simulate real lines on paper.
* **Cross-Platform Newlines:** Correctly handles both Windows (`\r\n`) and Unix (`\n`) line endings.

### Error Handling (Robustness)
* **File I/O:** Handles missing or inaccessible input/output files.
* **Format Validation:** Checks for the "BRL1" signature to prevent processing incompatible files.
* **Integrity Guard:** Stops execution if a Checksum mismatch is detected.
* **Edge Cases:** Handles empty files or files smaller than the minimum header size.

### Limitations & Future Improvements
* **Current Limitation:** Fixed line width (20 characters).
* **Planned Improvements:**
    * Add `-w [width]` argument for custom line widths (e.g., 40 chars for standard Braille paper).
    * Implement **Reverse Translation** (Binary -> ASCII).
    * Expand character support to **Unicode/UTF-8**.

---

## Testing Methodology

The application was tested using black-box functional testing at the console level.

1.  **Translation Test:**
    * **Input:** `test.txt` (containing letters, numbers, and punctuation).
    * **Result:** `result.brl` generated with the correct 32B header and expected payload size.
2.  **Visualization (Printer) Test:**
    * Verified that `result.brl` prints a correct ASCII grid.
    * *Example:* The letter 'n' correctly visualizes as `⠝`.
3.  **Stress & Error Test:**
    * **Manual Corruption:** Changed a single byte in `result.brl` via a hex editor. 
    * **Outcome:** Program successfully triggered: `Integrity check: FAILED`, proving the checksum logic works.

### Included Test Files
* `test.txt`: Sample text with phrases like `"nitra:;.(),"`.
* `result.brl`: Pre-generated binary file for immediate testing of the Printer mode.
