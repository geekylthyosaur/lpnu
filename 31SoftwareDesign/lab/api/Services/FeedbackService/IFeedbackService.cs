using api.DTO;

namespace api.Services.FeedbackService;

public interface IFeedbackService
{
    void AddFeedback(FeedbackDto feedback);
    FeedbackDto GetFeedback(int id);
    IEnumerable<FeedbackDto> GetFeedbacks();
    void UpdateFeedback(FeedbackDto feedback);
    void DeleteFeedback(int id);
}