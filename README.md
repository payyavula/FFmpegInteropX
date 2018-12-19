# FFmpegInterop library for Windows

#### This project is licensed under the [Apache 2.0 License](http://www.apache.org/licenses/LICENSE-2.0)

## Welcome to FFmpegInterop-lukasf (FFmpegUniversal branch)

FFmpegInterop is an open-source project that aims to provide an easy way to use **FFmpeg** in **Windows 10 UWP Apps**. This allows you to decode a lot of formats that are not natively supported on Windows 10.

FFmpegInterop-lukasf is a much **improved fork** of the original [Microsoft project](git://github.com/Microsoft/FFmpegInterop).

**Some of the important improvements:**

- Multiple audio stream support
- Subtitle support
- Audio effects (special thanks to [mcosmin222](https://github.com/mcosmin222)!)
- Stream information retrieval (name, language, format, etc)
- Passthrough of HEVC video for hardware decoding
- Major performance improvements (zero-copy data handling in all important areas)
- Frame grabber support
- API improvements
- Lots of bug fixes

**Other changes:**
- Support for Windows 8.x and Windows Phone 8.x has been dropped
- Visual Studio 2015 support has been dropped

## Building FFmpegUniversalSDK with Visual Studio 2017
- Please naviagate [https://github.com/M2Team/FFmpegUniversal](https://github.com/M2Team/FFmpegUniversal).

## Building FFmpegInterop library

After building ffmpeg with the steps above, you should find the ffmpeg libraries in the `FFmpegUniversal/FFmpegUniversalSDK/<architecture\>` folders.

Now you can build the FFmpegInterop library. 

Simply open the Visual Studio solution file `FFmpegInterop.sln`, set one of the MediaPlayer[CS/CPP/JS] sample projects as StartUp project, and run. FFmpegInterop should build cleanly giving you the interop object as well as the selected sample MediaPlayer (C++, C# or JS) that show how to connect the MediaStreamSource to a MediaElement or Video tag for playback.

### Using the FFmpegInterop object

Using the **FFmpegInteropMSS** object is fairly straightforward and can be observed from the sample applications provided.

1. Get an `IRandomAccessStream` for the media you want to playback.
2. Create a new `FFmpegInteropMSS` object using `FFmpegInteropMSS.CreateFromStreamAsync()` passing it the stream and optionally a config class instance.
3. Get the MediaPlaybackItem from the Interop object by invoking `CreateMediaPlaybackItem()`
4. Assign the MediaPlaybackItem to your MediaPlayer or MediaElement for playback.

Use `FFmepgInteropMSS.CreateFromUriAsync()` to create a MediaStreamSource on a streaming source (shoutcast for example).

You can use `FFmpegInteropMSS.GetMediaStreamSource()` to get the MediaStreamSource like in the original version of the library. But when using MediaStreamSource, you won't get subtitles. Subtitle support requires using the MediaPlaybackItem!

You can add a call to `FFmpegVersionInfo.CheckRecommendedVersion()` in your app startup code. This will raise an exception if you are using the lib with a version lower than the recommended version. This can help remind you to update ffmpeg after you updated FFmpegInterop.

Call `FrameGrabber.CreateFromStreamAsync()` to grab one or more frames from a video file.

## Integrating FFmpegInterop into your app solution

If you want to integrate FFmpegInterop into your app, you can just add the project file (`FFmpegInterop\Win10\FFmpegInterop\FFmpegInterop.vcxproj`) to your app solution as an existing project and add a reference from your main app project to FFmpegInterop. The FFmpegInterop project does not have to be in your app's solution folder. 

Additionally, your app must reference the ffmpeg dll files for the platform you are building. Best is to manually edit your app's project file. This allows you to refer the dlls built for the current platform using $BuildPlatform parameter.

For a C# project, you can do it like this:

```
  <ItemGroup>
    <Content Include="$(SolutionDir)FFmpegUniversal\Output\FFmpegUniversal\$(PlatformTarget)\Redist\*.dll" />
  </ItemGroup>
```

This assumes that the FFmpegInterop folder is located next to your solution folder and the ffmpeg build output folder contains exclusively the latest ffmpeg dlls. Paths might be different on your folder setup. For CPP and JS this can be done similarly, check the samples for reference.

## Credits / contributors

- [lukasf](https://github.com/lukasf)
- [mcosmin222](https://github.com/mcosmin222)
- [MouriNaruto](https://github.com/MouriNaruto)

Thank you also to Microsoft and the team who developed the original library!

## Your feedback is appreciated!
