package io.github.qwen;

import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class QwenParam {

    private int maxLength = 2048;

    private int maxContextLength = 512;

    private boolean doSample = true;

    private int topK;

    private float topP = 0.7f;

    private float temperature = 0.95f;

    private float repetitionPenalty = 1.0f;

    private int numThreads = Runtime.getRuntime().availableProcessors();
}
