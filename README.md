# Console-Video-Player
Watch videos you convert with video2console.exe!  
If you just want the exe, go [https://github.com/CVConverter/video-to-puretext-converter/releases](https://github.com/CVConverter/video-to-puretext-converter/releases) for releases.

![图片](https://user-images.githubusercontent.com/68136140/221356662-92c914b5-cf98-4daf-bd9d-a74ee894127b.png)


# How to use
## requirements
- Microsoft Windows 10 20H1 or higher(not tested on windows 11 or windows 7, you can try it yourself.)
- patience for at least 3 min

## run
drag targeting file(txt) to the exe file or just run the program and enter the targeting file path and audio(optional, use any single char to skip) path.  
(remember to remove the quotes when you are entering the file path!)  
by default, the audio should be the same name with video file(txt) but in wav format:  
  
the program can automatically play the relatived wav when you drag the video(txt) on the exe   
```
- C:\users\administrator\desktop\video-name.txt  <--  targeting video file(txt)
- C:\users\administrator\desktop\video-name.wav  <--  audio file of targeting video(must be wav format)
```
and those ones can't be automatically play by the program, you need to manualy enter their paths.
```
- C:\users\administrator\desktop\video-name.txt  <--  targeting video file(txt)
- C:\users\administrator\documents\video-name.wav <-- audio file is not in the same dir of targeting video file.
```
```
- C:\users\administrator\desktop\video-name.txt  <-- targeting video file(txt)
- C:\users\administrator\desktop\another-video-name.wav <-- audio file is not as the same name as targeting video file.
```
```
- C:\users\administrator\desktop\video-name.txt  <-- targeting video file(txt)
- C:\users\administrator\desktop\video-name.mp3 <-- audio file must in wav format.
```
  
## NOTICE
- if the video seems doesn't right, try maximze or full-screen the video player console window.  
(Try maximze full-screen the console before opening the video(set the default value))  
  
# How to compile and edit
## requirements:  
- Microsoft Windows 10 20H1 or higher(not tested on windows 11 or windows 7, you can try it yourself.)
- Microsoft Visual Studio 2022 with the latest C++ compiler(not tested on VS2019, you may try it yourself)
- C++ knowldge
*Warning: there is nearly no comment in the source code!!!*  
  
## before start
1. Create a new Visual Studio Project;
2. Import source code files from this repo.
3. If nothing went wrong, you can now compile your version.
