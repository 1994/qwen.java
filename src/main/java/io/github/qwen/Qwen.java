package io.github.qwen;

import java.lang.annotation.Native;

public class Qwen implements AutoCloseable {

    static {
        System.load(QwenConstant.getQwenLibrary());
    }
    @Native
    private long modelId;

    public Qwen(String model, String tiktokenPath) {
        load(model, tiktokenPath);
    }

    public String generate(String prompt) {
        return generate(prompt, new QwenParam());
    }

    public native String generate(String prompt,
                                  QwenParam param);

    private native void load(String modelPath, String tiktokenPath);

    private native void delete();

    @Override
    public void close() {
        delete();
    }
}
