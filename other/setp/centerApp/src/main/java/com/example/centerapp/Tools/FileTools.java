package com.example.centerapp.Tools;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileTools extends Object{
    private String mpath;
    private File mfile;
    private byte[] mreadbuff;

    public FileTools(String path){

        mpath = path;
        mfile = new File(path);
        mreadbuff = null;

    }

    public boolean exist(){

        return mfile.exists();
    }

    public void createNewFile() throws IOException {

        mfile.createNewFile();
    }

    public boolean write(String str){
        FileOutputStream fos = null;
        boolean ret = true;
        byte[] bytes = str.getBytes();

        try{

            fos = new FileOutputStream(mfile);
            fos.write(bytes);
            fos.close();
            fos = null;

        }catch (Exception ex){

            ret = false;
            ex.printStackTrace();
            if(fos != null){
                try {
                    fos.close();
                }catch (Exception e){}
            }
        }finally {
        }

        return ret;
    }

    public boolean readAll()  {

        FileInputStream fis = null;
        boolean ret = true;

        try{

            fis = new FileInputStream(mfile);
            mreadbuff = fis.readAllBytes();
            fis.close();
            fis = null;

        }catch (Exception ex){

            ret = false;
            ex.printStackTrace();
            if(fis != null) {

                try {
                    fis.close();
                }catch (Exception e){
                }
            }

        }finally {
        }

        return ret;
    }

    public String readbuff2String(){

        if(mreadbuff == null)
            return null;

        String ret = new String(mreadbuff);
        return ret;
    }

    public String[] readbuff2Lines(){

        String str = readbuff2String();
        if(str == null)
            return null;
        return str.split("\n");
    }
    public void clear(){

        mreadbuff = null;
    }
}
