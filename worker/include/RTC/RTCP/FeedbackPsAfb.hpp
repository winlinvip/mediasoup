#ifndef MS_RTC_RTCP_FEEDBACK_AFB_HPP
#define MS_RTC_RTCP_FEEDBACK_AFB_HPP

#include "common.hpp"
#include "RTC/RTCP/Feedback.hpp"

namespace RTC { namespace RTCP
{
	class FeedbackPsAfbPacket
		: public FeedbackPsPacket
	{
	public:
		typedef enum Application : uint8_t
		{
			UNKNOWN = 0,
			REMB = 1
		} Application;

	public:
		static FeedbackPsAfbPacket* Parse(const uint8_t* data, size_t len);

	public:
		// Parsed Report. Points to an external data.
		explicit FeedbackPsAfbPacket(CommonHeader* commonHeader, Application application = UNKNOWN);
		FeedbackPsAfbPacket(uint32_t sender_ssrc, uint32_t media_ssrc, Application application = UNKNOWN);
		virtual ~FeedbackPsAfbPacket() {};

		Application GetApplication();

	/* Pure virtual methods inherited from Packet. */
	public:
		virtual void Dump() override;
		virtual size_t Serialize(uint8_t* buffer) override;
		virtual size_t GetSize() override;

	private:
		Application application = UNKNOWN;
		uint8_t* data = nullptr;
		size_t size = 0;
	};

	/* Inline instance methods. */

	inline
	FeedbackPsAfbPacket::FeedbackPsAfbPacket(CommonHeader* commonHeader, Application application):
		FeedbackPsPacket(commonHeader)
	{
		this->size = ((ntohs(commonHeader->length) + 1) * 4) - (sizeof(CommonHeader) + sizeof(FeedbackPacket::Header));
		this->data = (uint8_t*)commonHeader + sizeof(CommonHeader) + sizeof(FeedbackPacket::Header);
		this->application = application;
	}

	inline
	FeedbackPsAfbPacket::FeedbackPsAfbPacket(uint32_t sender_ssrc, uint32_t media_ssrc, Application application):
		FeedbackPsPacket(FeedbackPs::AFB, sender_ssrc, media_ssrc)
	{
		this->application = application;
	}

	inline
	FeedbackPsAfbPacket::Application FeedbackPsAfbPacket::GetApplication()
	{
		return this->application;
	}

	inline
	size_t FeedbackPsAfbPacket::GetSize()
	{
		return FeedbackPsPacket::GetSize() + this->size;
	}
}}

#endif
