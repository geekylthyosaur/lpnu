using api.Models;

namespace api.Services.FeedbackService;

public class FeedbackService : IFeedbackService
{
    private readonly MyContext _myContext;

    public FeedbackService(MyContext myContext)
    {
        _myContext = myContext;
    }

    public void AddFeedback(Feedback feedback)
    {
        if (_myContext.Feedbacks.Find(feedback) is not null)
            throw new Exception("Already exists");
        _myContext.Feedbacks.Add(feedback);
    }

    public Feedback GetFeedback(int id)
    {
        var feedback = _myContext.Feedbacks.Find(id);
        if (feedback is null) throw new Exception("Not found");
        return feedback;
    }

    public IEnumerable<Feedback> GetFeedbacks()
    {
        return _myContext.Feedbacks.ToList();
    }

    public void UpdateFeedback(Feedback feedback)
    {
        if (_myContext.Feedbacks.Find(feedback) is null) throw new Exception("Not found");
        _myContext.Feedbacks.Update(feedback);
    }

    public void DeleteFeedback(int id)
    {
        var feedback = _myContext.Feedbacks.Find(id);
        if (feedback is null) throw new Exception("Not found");
        _myContext.Feedbacks.Remove(feedback);
    }
}