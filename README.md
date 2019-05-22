# Car Monitor

## Tips

This environment variable must be set in order to use UVC capture device (USB):

```sh
QT_GSTREAMER_CAMERABIN_VIDEOSRC=v4l2src ! jpegdec ! videoconvert
```
