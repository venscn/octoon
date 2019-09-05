#include "tool_window.h"

ToolBar::ToolBar(QWidget* parent)
	: gpuEnable_(false)
	, playEnable_(false)
{
	playIcon_ = QIcon::fromTheme("res", QIcon(":res/icons/play.png"));
	stopIcon_ = QIcon::fromTheme("res", QIcon(":res/icons/stop.png"));
	gpuIcon_ = QIcon::fromTheme("res", QIcon(":res/icons/gpu.png"));
	gpuOnIcon_ = QIcon::fromTheme("res", QIcon(":res/icons/gpu-on.png"));
	recordIcon_ = QIcon::fromTheme("res", QIcon(":res/icons/record.png"));
	recordOnIcon_ = QIcon::fromTheme("res", QIcon(":res/icons/recordOn.png"));

	hideButton_ = std::make_unique<QToolButton>(this);
	hideButton_->setIcon(QIcon::fromTheme("res", QIcon(":res/icons/hide.png")));
	hideButton_->setToolTip(u8"���ع�����");

	importButton_ = std::make_unique<QToolButton>(this);
	importButton_->setIcon(QIcon::fromTheme("res", QIcon(":res/icons/append.png")));
	importButton_->setToolTip(u8"�����ļ�");

	playButton_ = std::make_unique<QToolButton>(this);
	playButton_->setIcon(playIcon_);
	playButton_->setToolTip(u8"����");

	recordButton_ = std::make_unique<QToolButton>(this);
	recordButton_->setIcon(recordIcon_);
	recordButton_->setToolTip(u8"¼����Ƶ");

	shotButton_ = std::make_unique<QToolButton>(this);
	shotButton_->setIcon(QIcon::fromTheme("res", QIcon(":res/icons/shot.png")));
	shotButton_->setToolTip(u8"��ͼ");

	gpuButton_ = std::make_unique<QToolButton>(this);
	gpuButton_->setIcon(QIcon::fromTheme("res", QIcon(":res/icons/gpu.png")));
	gpuButton_->setToolTip(u8"��������Ⱦ");

	hdrButton_ = std::make_unique<QToolButton>(this);
	hdrButton_->setIcon(QIcon::fromTheme("res", QIcon(":res/icons/hdr.png")));
	hdrButton_->setToolTip(u8"���ظ߶�̬ͼ��");

	layout_ = std::make_unique<QVBoxLayout>(this);
	layout_->addWidget(hideButton_.get());
	layout_->addWidget(importButton_.get());
	layout_->addWidget(playButton_.get());
	layout_->addWidget(recordButton_.get());
	layout_->addWidget(shotButton_.get());
	layout_->addWidget(gpuButton_.get());
	layout_->addWidget(hdrButton_.get());
	layout_->addStretch();
	layout_->setSpacing(0);
	layout_->setContentsMargins(0, 0, 0, 0);

	this->connect(hideButton_.get(), SIGNAL(clicked()), this, SLOT(hideEvent()));
	this->connect(importButton_.get(), SIGNAL(clicked()), this, SLOT(importEvent()));
	this->connect(playButton_.get(), SIGNAL(clicked()), this, SLOT(playEvent()));
	this->connect(recordButton_.get(), SIGNAL(clicked()), this, SLOT(recordEvent()));
	this->connect(shotButton_.get(), SIGNAL(clicked()), this, SLOT(shotEvent()));
	this->connect(gpuButton_.get(), SIGNAL(clicked()), this, SLOT(gpuEvent()));
	this->connect(hdrButton_.get(), SIGNAL(clicked()), this, SLOT(hdrEvent()));

	this->setFixedWidth(42);
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

ToolBar::~ToolBar()
{
}

void
ToolBar::resizeEvent(QResizeEvent* e) noexcept
{
	hdrButton_->setFixedSize(width(), width());
	gpuButton_->setFixedSize(width(), width());
	shotButton_->setFixedSize(width(), width());
	recordButton_->setFixedSize(width(), width());
	hideButton_->setFixedSize(width(), width());
	importButton_->setFixedSize(width(), width());
	playButton_->setFixedSize(width(), width());
}

void
ToolBar::hideEvent() noexcept
{
	emit hideSignal();
}

void
ToolBar::importEvent() noexcept
{
	emit importSignal();
}

void
ToolBar::playEvent() noexcept
{
	if (!playEnable_)
	{
		emit playSignal(true);
		playButton_->setIcon(stopIcon_);
		playButton_->setToolTip(u8"ֹͣ");
		playEnable_ = true;
	}
	else
	{
		emit playSignal(false);
		playButton_->setIcon(playIcon_);
		playButton_->setToolTip(u8"����");
		playEnable_ = false;
	}
}

void
ToolBar::recordEvent() noexcept
{
	if (!recordEnable_)
	{
		emit recordSignal(true);
		recordButton_->setIcon(recordOnIcon_);
		recordEnable_ = true;
	}
	else
	{
		emit recordSignal(false);
		recordButton_->setIcon(recordIcon_);
		recordEnable_ = false;
	}
}

void
ToolBar::shotEvent() noexcept
{
	emit shotSignal();
}

void
ToolBar::gpuEvent() noexcept
{
	if (!gpuEnable_)
	{
		emit gpuSignal(true);
		gpuButton_->setIcon(gpuOnIcon_);
		gpuEnable_ = true;
	}
	else
	{
		emit gpuSignal(false);
		gpuButton_->setIcon(gpuIcon_);
		gpuEnable_ = false;
	}
}

void
ToolBar::hdrEvent() noexcept
{
	emit hdrSignal();
}