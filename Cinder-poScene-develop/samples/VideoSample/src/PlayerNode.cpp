#include "PlayerNode.h"

using namespace po::scene;

PlayerNodeRef PlayerNode::create()
{
    PlayerNodeRef node (new PlayerNode());
    node->setup();
    return node;
}

PlayerNode::PlayerNode() : mTexture(NULL)
{}

void PlayerNode::setup()
{
    //  create and add the video displayer
    //ci::fs::path moviePath = ci::app::getAssetPath("phoebe.mp4");
	ci::fs::path moviePath = ci::app::getAssetPath("test.mp4");
	mVideoDisplayer = VideoGl::create();
    
    try {
        ci::qtime::MovieGlRef movieRef;
        movieRef = ci::qtime::MovieGl::create(moviePath);
        mVideoDisplayer->setMovieRef(movieRef);
        mVideoDisplayer->getMovieRef()->play();

    } catch (...) {
        ci::app::console() << "PlayerNode::setup: Failed to load movie" << std::endl;
    }
	//mTexture->reset();

    getSignal(MouseEvent::Type::DOWN_INSIDE).connect(std::bind(&PlayerNode::clickVideo, this));
    addChild(mVideoDisplayer);
}

void PlayerNode::update()
{
    NodeContainer::update();
    
	if (!mVideoDisplayer->getMovieRef())
	{
		ci::app::console() << "PlayerNode::Failed to get movie ref" << std::endl;
		return;
	}
	
    //  when movie finishes, stop and go back to the beginning
    if (mVideoDisplayer->getMovieRef()->isPlaying()) {
        if (mVideoDisplayer->getMovieRef()->isDone()) {
            mVideoDisplayer->getMovieRef()->stop();
            mVideoDisplayer->getMovieRef()->seekToStart();
        }
    }
}

void PlayerNode::clickVideo()
{
    if (!mVideoDisplayer->getMovieRef()) return;
    if (mVideoDisplayer->getMovieRef()->isPlaying()) {
        mVideoDisplayer->getMovieRef()->stop();
    } else {
        mVideoDisplayer->getMovieRef()->play();
    }
}