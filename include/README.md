# **Literature Survey: PUF-Based Authentication in Healthcare Sector**

---

## **1. Securing the IoT-Enabled Smart Healthcare System: A PUF-Based Resource-Efficient Authentication Mechanism**

**[Link to Paper](https://pmc.ncbi.nlm.nih.gov/articles/PMC11416481/#se0050)**

### **Observations**

* Most protocols (\[24], \[29], \[39]) utilize **symmetric encryption** and **one-way hash functions** for lightweight and efficient cryptographic operations.

* **Formal verification** methods such as the **Scyther tool** and **Random-or-Real (RoR) model** are widely adopted to validate:

  * Mutual authentication
  * Session key secrecy
  * Resistance to replay, impersonation, and MITM attacks

* Identified security flaws in many existing schemes:

  * Offline password guessing
  * Insider and impersonation attacks   
  * Smart card/device capture
  * Lack of anonymity and untraceability

### **Motivation**

The paper evaluates various existing Authentication and Key Agreement (AKA) protocols and identifies key weaknesses:

* Replay and impersonation vulnerabilities
* Session key compromise
* Key escrow issues
* Absence of perfect forward secrecy
* Incomplete or missing formal security verification

### **Proposed Contribution**

Two new protocols designed for smart patient monitoring:

1. **IoTD-2-CS**: Authenticates IoT Devices to Cloud Server
2. **UX-2-CS**: Authenticates Users (e.g., doctors, nurses) to Cloud Server

### **Techniques Used**

* **Symmetric encryption**
* **One-way hash functions**
* **Physical Unclonable Functions (PUFs)** for device-level uniqueness

### **Security Features**

* Proven resistance against:

  * MITM
  * Replay
  * Impersonation
* Offers mutual authentication, forward secrecy, and data confidentiality

### **Performance Comparison**

| Protocol              | Computation Reduction | Communication Reduction |
| --------------------- | --------------------- | ----------------------- |
| UX-2-CS vs \[48–51]   | 69–86.25% ↓           | 25.55–56.85% ↓          |
| IoTD-2-CS vs \[52–55] | 75–95.80% ↓           | 35.24–74.62% ↓          |

---

## **2. PUFchain 3.0: Hardware-Assisted Distributed Ledger for Robust Authentication in Healthcare Cyber–Physical Systems**

**[Link to Paper](https://www.mdpi.com/1424-8220/24/3/938)**

### **PUF Types Used**

* **Arbiter PUF** (Patient's Gateway – BAN):
  Delay-based, lightweight, unique identity generation

* **XOR Arbiter PUF** (Edge Gateway):
  Improved security through non-linearity; resists ML attacks

### **Reasons for Selection**

* Low power consumption
* High reliability (\~99.7%), uniqueness (\~50%), uniformity (\~50%)
* Machine learning resilience

### **Blockchain Usage**

* Blockchain used to **encrypt and store medical transactions**
* Supports decentralized authentication and data integrity


### Hardware Implementation Details from "PUFchain 3.0"

- **PUF Types Used**: Arbiter PUF and XOR Arbiter PUF
- **Platform**: Xilinx Artix-7 Basys 3 FPGA (xc7a35tcpg236-1)
- **Technology Node**: Not explicitly mentioned (Artix-7 is 28nm)
- **Area Overhead**: Not specified
- **Power Consumption**: 0.081 Watts (on-chip)
- **PUF Key Instances**: 64-bit, tested with 1000 keys
- **Device Authentication Time**: ~3.66 seconds


---

## **3. Blockchain-Based Mutual Authentication Protocol for IoT-Enabled Decentralized Healthcare Environment**

**[Link to Paper](https://ieeexplore.ieee.org/abstract/document/10530180)**

### **System Overview**

Entities: Doctor (DR), Medical Robot (MR), Patient (PT), Cloud Server (CS), Hospital (HP)
Phases:

* **Registration**: Biometric + password-based identity creation via fuzzy extractors
* **Authentication and Key Agreement**: Three sub-protocols (DR↔MR, MR↔CS, MR↔PT)
* **Blockchain Storage**: Treatment data encrypted and stored using ECDSA and PBFT

### **Encryption Techniques**

| Technique                | Purpose                                          |
| ------------------------ | ------------------------------------------------ |
| SHA-based Hash Functions | Pseudonymization, key derivation, integrity      |
| XOR                      | Obfuscation, lightweight cryptographic operation |
| AES-128 (CBC)            | Encrypting sensitive tokens                      |
| Fuzzy Extractors         | Biometric key extraction                         |
| ECDSA                    | Digital signatures for blockchain blocks         |
| ECC                      | Lightweight asymmetric encryption                |
| IND-CPA Secure Cipher    | Chosen-plaintext resistance                      |

---

## **4. PAAF-SHS: PUF and Authenticated Encryption-Based Authentication Framework for IoT-Enabled Smart Healthcare Systems**

**[Link to Paper](https://www.sciencedirect.com/science/article/pii/S2542660524001008)**

### **PUF Usage**

* Exact PUF type not specified
* **Generic CRP-based PUF** used
* Stabilized using **fuzzy extractors** to generate consistent keys

### **Architecture Entities**

* **Trusted Authority (TA)**
* **Medical Server (MS)**
* **User Device (Doctors/Nurses)**

### **Authentication Flow**

* **Enrollment**:
  TA sends challenges → Devices compute PUF responses → Extracted keys via FE

* **Authentication & Key Agreement**:
  Users input biometric + credentials → Device regenerates key →
  Mutual authentication using lightweight **GIFT-COFB** encryption

### **Encryption Scheme: GIFT-COFB**

* Lightweight authenticated encryption
* Produces ciphertext + authentication tag
* Chosen for NIST lightweight crypto suitability

---

## **5. Securing IoT-Based Smart Healthcare Systems Using Advanced Lightweight Privacy-Preserving Authentication**

**[Link to Paper](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=10148997)**

### **PUF Model**

* Generic CRP-based PUF: $R = P(C)$
* Integrated with **fuzzy extractors** for reliable key regeneration
* No specific architecture mentioned

### **Encryption Techniques**

* **SHA-2**: Used for temporary identity, session key derivation, and message authentication
* **XOR**: Lightweight message obfuscation
* **PUF + FE**: CRP-based keys without storing secrets

### **Protocol Phases**

1. **System Initialization**
2. **Device Registration**
3. **Authentication and Key Agreement**
4. **Credential Update**

### **Security Features**

* No key storage in devices
* Mutual authentication and anonymity
* Resistance to:

  * Replay, MITM
  * Physical capture
  * Desynchronization and impersonation attacks

---

## **6. Lightweight Cloud Computing-Based RFID Authentication Protocols Using PUF for E-Healthcare Systems**

**[Link to Paper](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=10041027&tag=1)**

### **PUF Type Used**

* **Barrel Shifter PUF (BS-PUF)**

  * **Invertible**: Allows key recovery
  * **Commutative**: $PUF_1(PUF_2(x)) = PUF_2(PUF_1(x))$

### **Encryption Methods**

* **Hash Functions (SHA)**: Identity masking and integrity
* **XOR**: Lightweight cryptography
* **PUF-based key exchange**: No stored keys required

### **Protocol Types**

1. **Type-1** (Reader & CS Combined)
2. **Type-2** (Reader ↔ Cloud Separation)

### **Security Properties**

* Mutual authentication
* Anonymity and untraceability
* Perfect forward/backward secrecy
* Resistance to:

  * Replay and ML attacks
  * Physical compromise
  * Desynchronization and MITM attacks

##

# 7. A PUF-based anonymous authentication protocol for wireless medical sensor networks

**[paper link](https://link.springer.com/article/10.1007/s11276-022-03070-1)**


| **Aspect**              | **Details**                                                              |
| ----------------------- | ------------------------------------------------------------------------ |
| **Type of PUF**         | Abstract PUF with challenge-response pairs; likely SRAM/RO/Arbiter PUF   |
| **Area Overhead**       | Not quantified; claimed lightweight and suitable for constrained devices |
| **Technology Node**     | Not specified                                                            |
| **Encryption Protocol** | Uses hash functions, XOR, fuzzy extractors instead of AES/ECC            |

##

# 8. On the Security of a Blockchain and PUF‑Based Lightweight Authentication Protocol for Wireless Medical Sensor Networks

**[paper link](https://link.springer.com/content/pdf/10.1007/s11277-024-11318-6.pdf)**

| Parameter                            | Value / Info                                                      |
| ------------------------------------ | ----------------------------------------------------------------- |
| **PUF Type**                         | Not specified (assumed digital, challenge-response based)         |
| **Area Overhead**                    | Not quantified, but shown feasible on ATmega328 (2KB SRAM, 16MHz) |
| **Technology Node**                  | Not specified, but ATmega328 MCU implies 350–600nm                |
| **Encryption / Cryptographic Tools** | Hash functions, XOR operations, fuzzy extractors                  |
| **Formal Security Models Used**      | AVISPA (OFMC & ATSE), Random Oracle Model                         |

##

# 9. A Lightweight PUF Based Multi‑factor Authentication Technique for Intelligent Smart Healthcare System

**[paper link](https://link.springer.com/article/10.1007/s12083-023-01509-6)**


| **Parameter**               | **Details**                                                                                                                                                |
| --------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Type of PUF Used**        | CRC-PUF (based on Arbiter PUF)                                                                                                                             |
| **PUF Architecture**        | 16-bit Fibonacci LFSR with feedback polynomial $X^{16} + X^{14} + X^{13} + X^{11}$                                                                         |
| **Security Features**       | Enhances unpredictability and resists ML/modeling attacks                                                                                                  |
| **Technology Node**         | 0.13 µm CMOS standard cell library                                                                                                                         |
| **Area Overhead (in GE)**   | **\~181 GE total**, with breakdown:<br> • NAND (2-input): 1<br> • AND (2-input): 1.5<br> • XOR (2-input): 2.5<br> • Flip-Flop: 6.25<br> • MUX (2:1): 169.8 |
| **Application Suitability** | Designed for lightweight, low-power IoT devices in smart healthcare systems                                                                                |

##

# 10. Enhancing the Security: A Lightweight Authentication and Key Agreement Protocol for Smart Medical Services in the IoHT


**[paper link](https://www.researchgate.net/publication/373476294_Enhancing_the_Security_A_Lightweight_Authentication_and_Key_Agreement_Protocol_for_Smart_Medical_Services_in_the_IoHT)**



## What is this Protocol About?

A secure login and communication protocol for doctors and medical sensors in an Internet of Health Things (IoHT) system. It ensures that data shared between the doctor (user) and sensor is authenticated and encrypted via a trusted gateway (GWN).

---

## Main Components

* **Doctor (Ui)**: The user who needs access to health data.
* **Sensor (Sj)**: Medical device collecting patient data.
* **Gateway Node (GWN)**: Connects doctors and sensors securely.

---

## 1. Registration Phase

### Doctor's Registration

* Doctor selects `IDi`, `PWi` (password), and secret `ai`.
* Sends hidden credentials (`TIDi`, `ai`) to GWN.
* GWN creates a token (`UMi`) and stores associated info.
* Doctor stores authentication data on a smartcard or device.

### Sensor’s Setup

* Sensor chooses `IDSj` and random number `cj`.
* Sends info to GWN.
* GWN computes secret code (`SMj`) and sends to sensor.
* Sensor stores `SMj` securely for future verification.

---

## 2. Login and Authentication Phase

### Step 1: Doctor Logs In

* Inputs `IDi` and `PWi`.
* Local device verifies credentials.
* Sends authentication message to GWN requesting access to sensor.

### Step 2: Gateway Checks

* GWN verifies doctor’s identity using stored records.
* Forwards access request to the target sensor.

### Step 3: Sensor Verifies

* Sensor authenticates the request.
* If valid, creates a response and shares a key component (`Rj`).

### Step 4: Gateway Sends Final Info

* GWN combines doctor and sensor info.
* Sends the final message to the doctor for confirmation.

### Step 5: Secure Session Established

* Doctor verifies the final message.
* Both doctor and sensor compute the same session key (`SK`).
* All communication is now encrypted using `SK`.

---

## Why is This Protocol Better?

* Protects identity and password information using hashing and pseudonyms.
* Secure against passive (eavesdropping) and active (replay, impersonation) attacks.
* Lightweight cryptographic operations make it efficient for IoHT devices.
* Enables mutual authentication and key agreement without exposing secrets.

##

# 11. PUF-PSS: A Physically Secure Privacy-Preserving Scheme Using PUF for IoMT-Enabled TMIS 

**[paper link](https://www.mdpi.com/2079-9292/11/19/3081?utm_source=chatgpt.com)**


### PUF-PSS (Electronics 2022)

- **PUF Type**: SRAM-PUF (conceptually suitable for constrained devices)
- **Technology Node**: Not fabricated; tested on Raspberry Pi 4 and desktop
- **Area Overhead**: Not reported; qualitative claim of low overhead (XOR + hash only)
- **Authentication**: Biometric + password + PUF binding
- **Execution Platform**:
  - Raspberry Pi 4B (1.5 GHz Quad-core ARM, Ubuntu 20.04)
  - Intel Core i5-10400 Desktop (Ubuntu 18.04)

- **No hardware implementation** in ASIC/FPGA, hence no gate-level area data or fabrication node

##
# 12. A PUF-based anonymous authentication protocol for wireless medical sensor networks

**[paper link](https://link.springer.com/content/pdf/10.1007/s11276-022-03070-1.pdf)**

| **Aspect**              | **Details**                                                              |
| ----------------------- | ------------------------------------------------------------------------ |
| **Type of PUF**         | Abstract PUF with challenge-response pairs; likely SRAM/RO/Arbiter PUF   |
| **Area Overhead**       | Not quantified; claimed lightweight and suitable for constrained devices |
| **Technology Node**     | Not specified                                                            |
| **Encryption Protocol** | Uses hash functions, XOR, fuzzy extractors instead of AES/ECC            |

##

# 13. On the Security of a Blockchain and PUF‑Based Lightweight Authentication Protocol for Wireless Medical Sensor Networks

**[paper link](https://link.springer.com/content/pdf/10.1007/s11277-024-11318-6.pdf)**

  | Parameter                            | Value / Info                                                      |
| ------------------------------------ | ----------------------------------------------------------------- |
| **PUF Type**                         | Not specified (assumed digital, challenge-response based)         |
| **Area Overhead**                    | Not quantified, but shown feasible on ATmega328 (2KB SRAM, 16MHz) |
| **Technology Node**                  | Not specified, but ATmega328 MCU implies 350–600nm                |
| **Encryption / Cryptographic Tools** | Hash functions, XOR operations, fuzzy extractors                  |
| **Formal Security Models Used**      | AVISPA (OFMC & ATSE), Random Oracle Model                         |
         
## 
# 14. ASAP: A lightweight authenticated secure association protocol for IEEE 802.15.6 based medical BAN

**[paper link](https://www.sciencedirect.com/science/article/pii/S2542660524003044)**


| Aspect          | ASAP Protocol                                      |
| --------------- | -------------------------------------------------- |
| PUF Used?       |  No (referenced but not implemented)              |
| Technology Node |  Not specified (uses Arduino, Raspberry Pi, COTS) |
| Area Overhead   |  Not reported (optimized for constrained devices) |
| Encryption      | ECC (ECDH, ECDSA), EC-ElGamal, AES-128 CCM, CMAC   |
| Certs           | ECQV implicit certs (lightweight)                  |
| Session Keys    | PTK (pairwise), GTK (group)                        |

