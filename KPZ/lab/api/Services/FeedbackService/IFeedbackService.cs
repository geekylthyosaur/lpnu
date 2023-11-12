using api.Models;

namespace api.Services.FeedbackService;

public interface IFeedbackService
{
    void AddFeedback(Feedback feedback);
    Feedback GetFeedback(int id);
    IEnumerable<Feedback> GetFeedbacks();
    void UpdateFeedback(Feedback feedback);
    void DeleteFeedback(int id);
}