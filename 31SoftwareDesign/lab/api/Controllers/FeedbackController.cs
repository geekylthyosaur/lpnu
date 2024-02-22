using api.DTO;
using api.Services.FeedbackService;
using Microsoft.AspNetCore.Mvc;

namespace api.Controllers;

[ApiController]
    [Route("[controller]/")]
    public class FeedbackController : ControllerBase
    {
        private readonly IFeedbackService _feedbackService;

        public FeedbackController(IFeedbackService feedbackService)
        {
            _feedbackService = feedbackService;
        }

        [HttpPost(Name = "AddFeedback")]
        public ActionResult AddFeedback([FromBody] FeedbackDto feedback)
        {
            try
            {
                _feedbackService.AddFeedback(feedback);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpGet("{id:int}", Name = "GetFeedback")]
        public ActionResult<FeedbackDto> GetFeedback(int id)
        {
            try
            {
                var feedback = _feedbackService.GetFeedback(id);
                return Ok(feedback);
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpGet(Name = "GetFeedbacks")]
        public ActionResult<IEnumerable<FeedbackDto>> GetFeedbacks()
        {
            try
            {
                var feedbacks = _feedbackService.GetFeedbacks();
                return Ok(feedbacks);
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpPut(Name = "UpdateFeedback")]
        public ActionResult UpdateFeedback([FromBody] FeedbackDto feedback)
        {
            try
            {
                _feedbackService.UpdateFeedback(feedback);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpDelete("{id:int}", Name = "DeleteFeedback")]
        public ActionResult DeleteFeedback(int id)
        {
            try
            {
                _feedbackService.DeleteFeedback(id);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }
    }