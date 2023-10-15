package io.github.qwen;

import java.io.File;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class QwenConstant {

    private static final String LIB_NAME = "libqwen-java";

    public static String getLibName() {
        String osName = System.getProperty("os.name");

        if (osName.startsWith("Linux")) {
            return String.format("%s.so", LIB_NAME);
        } else if (osName.startsWith("Mac")) {
            return String.format("%s.dylib", LIB_NAME);
        } else {
            throw new UnsupportedOperationException(String.format("unsupported platform, osName:%s", osName));
        }
    }

    public static String getLibraryPath() {
        List<String> result = new ArrayList<>(3);
        result.add("lib");
        String osName = System.getProperty("os.name");
        if (osName.startsWith("Linux")) {
            result.add("linux");
        } else if (osName.startsWith("Mac")) {
            result.add("macos");
        }
        return String.join(File.separator, result);
    }

    public static String getQwenLibrary() {
        ClassLoader classLoader = QwenConstant.class.getClassLoader();
        String path = getLibraryPath() + File.separator + getLibName();
        URL resourceURL = classLoader.getResource(path);
        if (Objects.isNull(resourceURL)) {
            throw new UnsupportedOperationException();
        }
        return resourceURL.getPath();
    }
}
