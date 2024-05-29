public class Level2SupportHandler implements SupportHandler {
    private SupportHandler nextHandler;
 
    public void setNextHandler(SupportHandler nextHandler) {
        this.nextHandler = nextHandler;
    }
 
    public void handleRequest(Request request) {
        if (request.getPriority() == Priority.INTERMEDIATE) {
            System.out.println("Level 2 Support handled the request.");
        } else if (nextHandler != null) {
            nextHandler.handleRequest(request);
        }
    }
}