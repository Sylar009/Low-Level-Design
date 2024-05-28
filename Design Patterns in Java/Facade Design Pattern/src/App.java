public class App {
    public static void main(String[] args) throws Exception {
        MultimediaFacade facade = new MultimediaFacade();
 
        // Playing audio
        facade.playMedia("song.mp3", "audio");
 
        // Playing video
        facade.playMedia("movie.mp4", "video");
 
        // Loading image
        facade.playMedia("picture.jpg", "image");
 
        // Unsupported media type
        facade.playMedia("unknown.file", "unknown");
    }
}
