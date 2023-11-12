using api.DTO;
using api.Models;
using AutoMapper;

namespace api.Services.FeedbackService;

public class FeedbackService : IFeedbackService
{
    private readonly MyContext _myContext;
    private readonly IMapper _mapper;

    public FeedbackService(MyContext myContext, IMapper mapper)
    {
        _myContext = myContext;
        _mapper = mapper;
    }

    public void AddFeedback(FeedbackDto feedback)
    {
        if (_myContext.Feedbacks.Find(feedback) is not null)
            throw new Exception("Already exists");
        _myContext.Feedbacks.Add(_mapper.Map<Feedback>(feedback));
    }

    public FeedbackDto GetFeedback(int id)
    {
        var feedback = _myContext.Feedbacks.Find(id);
        if (feedback is null) throw new Exception("Not found");
        return _mapper.Map<FeedbackDto>(feedback);
    }

    public IEnumerable<FeedbackDto> GetFeedbacks()
    {
        return _mapper.Map<IEnumerable<FeedbackDto>>(_myContext.Feedbacks.ToList());
    }

    public void UpdateFeedback(FeedbackDto feedback)
    {
        if (_myContext.Feedbacks.Find(feedback) is null) throw new Exception("Not found");
        _myContext.Feedbacks.Update(_mapper.Map<Feedback>(feedback));
    }

    public void DeleteFeedback(int id)
    {
        var feedback = _myContext.Feedbacks.Find(id);
        if (feedback is null) throw new Exception("Not found");
        _myContext.Feedbacks.Remove(feedback);
    }
}