![Java 11+](https://img.shields.io/badge/Java-11%2B-informational)

# Java Bindings for [Qwen.cpp](https://github.com/QwenLM/qwen.cpp)
This repository provides Java bindings for the `qwen.cpp` c++ library and high level API for inference Qwen model.

# Prerequisites
- JDK 11 or higher
- Operating System Support: macOS and linux(arm64) 

**Please Note: The current project does not support Windows. See [here](https://github.com/QwenLM/qwen.cpp/issues/5)**

# Quick start
add maven dependency:

```xml
<dependency>
    <groupId>io.github.1994</groupId>
    <artifactId>qwen-java</artifactId>
    <version>1.0-SNAPSHOT</version>
</dependency>
```
**Please Note: The Maven coordinates for this project are currently pending approval and are not yet active.**

Here is a short example:

```java

try (Qwen qwen = new Qwen(/path/to/qwen/bin, /path/to/qwen/tiktoken) {
    String hello = qwen.generate("hello");
}


```
![img.png](img.png)
