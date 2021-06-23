package com.example.centerapp.Tools;

import org.luaj.vm2.ast.Str;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import sun.jvm.hotspot.runtime.linux_sparc.LinuxSPARCJavaThreadPDAccess;

public interface StringFindBackKey{
    String get(String key) throws Exception;
}
