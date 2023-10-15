![Java 11+](https://img.shields.io/badge/Java-11%2B-informational)

# Java Bindings for [Qwen.cpp](https://github.com/QwenLM/qwen.cpp)
This repository provides Java bindings for the c++ library.

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
